#include "drive.h"
#include "Odom/Math.h"
#include "motionProfiling.h"
#include "okapi/api/odometry/odomState.hpp"
#include "okapi/api/units/QAcceleration.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QSpeed.hpp"
#include "parameters.h"
#include "odom/OdomArc.h"
#include "pros/rtos.h"
#include <cmath>
#include "moveParams.h"

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
    optional<QAcceleration> max_acc,
    optional<QTime> timeout,
    optional<QLength> end_tolerance
) {
    // ========= Set Optional to Defaults defined in moveParams.h ========= 
    if (point_tolerance == nullopt) point_tolerance = POINT_TOLERANCE;
    if (max_acc == nullopt) max_acc = MAX_ACCELERATION;
    if (timeout == nullopt) timeout = TIMEOUT;
    if (end_tolerance == nullopt) end_tolerance = END_TOLERANCE;

    // ============= Setup Main Loop ============= 
    OdomArc::resetDistTravelled();
    MotionProfiling mt_profile (points, *max_acc);
    double current_kp = points.begin()->kp;

    DistancePID.reset();
    HeadingPID.reset();

    QLength lookahead_dist = points.begin()->lookaheadDistance; 
    int pointIdx = 0; // last point that we hit

    auto start = pros::c::millis();
    bool mainLoop = true;
    bool is_reverse = Math::anglePoint(OdomArc::getPos(), (points.begin()+1)->point) > 90_deg;

    // ============= Main Loop ============= 
    while (mainLoop) {
        // ============= Get current conditions ============= 
        QTime elapsed = (pros::c::millis() - start) * 1_ms;
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

        // ============= Calculate the motion profiling & forward motion vel ============= 
        QLength dist_err = (mt_profile.dist(elapsed) - OdomArc::getDistTravelled());
        double fw_motor_vel = dist_err.convert(okapi::inch) * current_kp;
    
        // ============= Find Goal Point for Heading ============= 
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
            auto d = Math::distance(heading_point, p).convert(okapi::inch);
            if (shortest_distance == -1 || d < shortest_distance) {
                shortest_distance = d;
                target_point = p;
            }
        }

        // find angle error (if valid point. Else, we assume 0_deg angle err)
        QAngle angle_err = 
            (target_point.x != -1_in && target_point.y != -1_in) ? 
                Math::anglePoint(current_pos, target_point) 
            : 0_deg;

        // angle motor vel
        QSpeed target_vel = mt_profile.vel(elapsed);
        double ang_motor_vel = ROBOT_WIDTH.convert(okapi::foot) * sin(angle_err.convert(radian)) / lookahead_dist.convert(okapi::foot) * target_vel.convert(fps);
        
        // ============= Move Robot! ============= 
        drive.moveArcade(
            fw_motor_vel * (is_reverse ? -1 : 1),
            ang_motor_vel
        );

        // ============= Check if end program ============= 
        if (
            (elapsed >= (mt_profile.get_total_time() + (*timeout))) ||  // timeout
            (abs(dist_err) <= (*end_tolerance))                    // end tolerance
        ) {
            mainLoop = false;
            break;
        }

        // ============= Delay ============= 
        pros::delay(10);
    }

    drive.moveArcade(0,0); // ensure movement stops at end.

}