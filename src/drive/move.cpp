#include "drive.h"
#include "Odom/Math.h"
#include "motionProfiling.h"
#include "okapi/api/odometry/odomState.hpp"
#include "okapi/api/units/QAcceleration.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QSpeed.hpp"
#include "okapi/api/units/QTime.hpp"
#include "parameters.h"
#include "odom/OdomArc.h"
#include "pros/rtos.h"
#include <cmath>
#include <sys/_intsup.h>
#include "moveParams.h"
#include "pros/rtos.hpp"

QLength calcXDist (okapi::OdomState current_pos, okapi::Point target_point) {
    // this is a simplified calculation of taking the projection vector of the x-axis (<cos(theta), -sin(theta)> in our coordinate system) as u
    // and the displacement vector <target - current position> as v
    // proj_u (v)

    return cos(current_pos.theta) * (target_point.x - current_pos.x) - sin(current_pos.theta) * (target_point.y - current_pos.y);
}

DrivePoint :: DrivePoint (
    okapi::Point point, 
    optional<okapi::QLength> lookaheadDistance,
    optional<okapi::QSpeed> max_speed,
    optional<double> kp,
    optional<std::function<void()>> callback
) {
    this->point = point;
    this->lookaheadDistance = (lookaheadDistance == nullopt) ? LOOKAHEAD_DIST : (*lookaheadDistance);
    this->max_speed = (max_speed == nullopt) ? MAX_SPEED : (*max_speed);
    this->kp = (kp == nullopt) ? KP : (*kp);
    this->callback = callback;
}

void Drive::move (
    std::initializer_list<DrivePoint> points,
    optional<QLength> point_tolerance,
    optional<QAcceleration> accel,
    optional<QTime> timeout,
    optional<QLength> end_tolerance
) {
    // ========= Set Optional to Defaults defined in moveParams.h ========= 
    if (point_tolerance == nullopt) point_tolerance = POINT_TOLERANCE;
    if (accel == nullopt) accel = MAX_ACCEL;
    if (timeout == nullopt) timeout = TIMEOUT;
    if (end_tolerance == nullopt) end_tolerance = END_TOLERANCE;

    // ============= Setup Main Loop ============= 
    OdomArc::resetDistTravelled();
    MotionProfiling mt_profile (points, *accel);
    double current_kp = points.begin()->kp;

    QLength lookahead_dist = points.begin()->lookaheadDistance; 
    int pointIdx = 0; // last point that we hit

    QTime start_time = pros::c::millis() * 1_ms;
    bool mainLoop = true;
    bool is_reverse = Math::anglePoint(OdomArc::getPos(), (points.begin()+1)->point).abs() > 90_deg;

    QLength max_err = 0_in;
    QLength min_err = 0_in;
    bool stbool = false;

    unsigned int i = 0;

    QSpeed prev_left_vel = 0_fps;
    QSpeed prev_right_vel = 0_fps;
    QTime prev_time = start_time;

    QAcceleration left_vel_acc = 0_fps2;
    QAcceleration right_vel_acc = 0_fps2;
    
    // ============= Main Loop ============= 
    while (mainLoop) {
        // ============= Delay ============= 
        pros::delay(10);
        
        // ============= Get current conditions ============= 
        auto current_pos = OdomArc::getPos();
        current_pos.theta += (is_reverse ? 180_deg : 0_deg); // if reverse, act like we are going forward (we reverse motor direction)

        // ======== Set lookahead distance, kp, and call callback ======
        // max speed, acceleration, and curvature speed are accounted for throughout the path in motion profiling 
        for (int i = pointIdx; i < points.size(); i++) {
            auto drive_point = *(points.begin() + i);
            if (Math::distance(current_pos, drive_point.point) <= (*point_tolerance)) {
                lookahead_dist = drive_point.lookaheadDistance;
                current_kp = drive_point.kp;
                if (drive_point.callback) (*drive_point.callback)();
                pointIdx++;
                break;
            }
        }

        // ============= Find Goal Point ============= 
        vector<Point> pot_points = {}; 
        Point target_point = {-1_in, -1_in};

        // go through each path and add to pot_points
        for (int x = 0; x < points.size()-1; x++) { 
            auto result = Math::circleLineIntersection(
                {current_pos.x, current_pos.y},
                lookahead_dist,
                (points.begin() + x)->point,
                (points.begin() + x + 1)->point
            );

            for (auto p : result) pot_points.push_back(p);
        }
        
        // out of all points, find one closest to heading point
        auto heading_point = Math::findPointOffset(current_pos, lookahead_dist);
        double shortest_distance = -1;
        for (auto p : pot_points) {
            if (Math::anglePoint(current_pos, p).abs() > 150_deg) continue;
            auto d = Math::distance(heading_point, p).convert(okapi::foot);
            if (shortest_distance == -1 || d < shortest_distance) {
                shortest_distance = d;
                target_point = p;
            }
        }

        // Output: target_point
        
        // ============= Move Robot ============= 
        // Find current time
        QTime current_time = pros::millis() * 1_ms;
        
        // find the curvature of arc to go to the target point 
        double curvature = 
            (target_point.x != -1_in && target_point.y != -1_in) ?
                (2 * calcXDist(current_pos, target_point).convert(foot))/pow(lookahead_dist.convert(foot), 2)  // 1/foot
            :
                0.0;
        
        // get left/right target velocity from motion profiling + curvature
        QTime elapsed = current_time - start_time;
        QSpeed forward_vel = mt_profile.vel(elapsed);
        QSpeed left_vel = (forward_vel.convert(fps) * (2.0 + curvature*ROBOT_WIDTH.convert(foot))/2.0) * 1_fps; 
        QSpeed right_vel = (forward_vel.convert(fps) * (2.0 - curvature*ROBOT_WIDTH.convert(foot))/2.0) * 1_fps;
        
        // calculate left vel acc and right vel acceleration
        if (i % 5 == 0) {
            QTime deltaT = current_time - prev_time;
            left_vel_acc = (left_vel - prev_left_vel) / deltaT;
            right_vel_acc = (right_vel - prev_right_vel) / deltaT;

            prev_left_vel = left_vel;
            prev_right_vel = right_vel;
            prev_time = current_time;
        }

        // calculate feed forward of both vel and acc for each side of drivebase
        double ff_left = KV * left_vel.convert(fps) + KA * left_vel_acc.convert(fps2);
        double ff_right = KV * right_vel.convert(fps) + KA * right_vel_acc.convert(fps2);
        
        // set motor voltages
        leftMotorGroup.moveVoltage(ff_left * 120); // 12000 is max: 12000/100 --> 120; 100 is full output
        rightMotorGroup.moveVoltage(ff_right * 120); // 100 is full output
        
        // ============= Debug ============= 
        if (true && i % 10 == 0) {
            printf("* Current: %f *\n", OdomArc::getCurrentSpeed().convert(tps));
            printf("* Target: %f *\n", forward_vel.convert(tps));
            printf("* Curv: %f *\n", curvature);
        }

        // ============= Check if end program ============= 
        // if (
        //     (elapsed >= (mt_profile.get_total_time() + (*timeout)))  // timeout
        // ) {
        //     printf("Timeout -- done\n");
        //     mainLoop = false;
        //     break;
        // }
        
        auto total_dist_travelled = OdomArc::getDistTravelled();
        if (
            (abs(mt_profile.get_total_distance() - total_dist_travelled) <= (*end_tolerance))                    // end tolerance
        ) {
            printf("Total distance travelled -- done\n");
            mainLoop = false;
            break;
        }

        i += 1;
    }

    leftMotorGroup.moveVoltage(0); 
    rightMotorGroup.moveVoltage(0); 
}