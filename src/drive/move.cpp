#include "controller.h"
#include "Console.h"
#include "drive.h"
#include "Odom/Math.h"
#include "okapi/api/odometry/odomState.hpp"
#include "okapi/api/odometry/point.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include "parameters.h"
#include "odom/OdomArc.h"
#include "pros/rtos.h"
#include <cmath>
#include <stdexcept>
#include "moveParams.h"

// Pure pursuit implementation

QLength calcXDist (okapi::OdomState current_pos, okapi::Point target_point) {
    // this is a simplified calculation of taking the projection vector of the x-axis (<cos(theta), -sin(theta)> in our coordinate system) as u
    // and the displacement vector <target - current position> as v
    // proj_u (v)

    return cos(current_pos.theta) * (target_point.x - current_pos.x) - sin(current_pos.theta) * (target_point.y - current_pos.y);
}

DrivePoint :: DrivePoint (
    okapi::Point point, 
    optional<okapi::QLength> lookaheadDistance,
    optional<std::function<void()>> callback
) {
    this->point = point;
    this->lookaheadDistance = (lookaheadDistance == nullopt) ? LOOKAHEAD_DIST : (*lookaheadDistance);
    this->callback = callback;
}

void Drive::move (
    std::initializer_list<DrivePoint> points,
    optional<QLength> point_tolerance,
    optional<QLength> end_tolerance,
    optional<QTime> timeout
) {
    // ========= Set Optional to Defaults defined in moveParams.h ========= 
    if (point_tolerance == nullopt) point_tolerance = POINT_TOLERANCE;
    if (timeout == nullopt) timeout = TIMEOUT;
    if (end_tolerance == nullopt) end_tolerance = END_TOLERANCE;

    // ============= Setup Main Loop ============= 
    QLength lookahead_dist = points.begin()->lookaheadDistance; 
    int pointIdx = 0; // last point that we hit

    auto start = pros::c::millis();
    bool mainLoop = true;
    bool is_reverse = Math::anglePoint(
        OdomArc::getPos(), 
        (points.begin()+1)->point
    ).abs() > 90_deg;

    QLength max_err = 0_in;
    QLength min_err = 0_in;
    bool stbool = false;
    
    unsigned int i = 0;

    // ============= Main Loop ============= 
    printf("Started\n");
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
                if (drive_point.callback) (*drive_point.callback)();
                pointIdx++;
                break;
            }
        }

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

        // If we can't find the target point but we are on the second to last point of the path, just set it to the target point
        bool is_using_targetp = false;
        if (pointIdx == points.size() - 2 && target_point.x == -1_in && target_point.y == -1_in) {
            target_point = points.end()->point;
            is_using_targetp = true;
        }

        // find angle error (if valid point. Else, we assume 0_deg angle err)
        QAngle angle_err = 
            (target_point.x != -1_in && target_point.y != -1_in) ? 
                Math::anglePoint(current_pos, target_point) 
            : 0_deg;

        // ===== FOR DEBUGGING ===== 
        if (target_point.x == -1_in && target_point.y == -1_in) {
            // STOP completely
            drive.moveArcade(0, 0);
            printf("Target point not found; \n");
            throw invalid_argument("Target point not found");
            mainLoop = false;
            break; 
        }

        // ============= Calculate the forward and turning vel ============= 
        double fw_motor_vel = P_DIST * Math::distance(current_pos, target_point).abs().convert(inch);
        double curvature = (2 * calcXDist(current_pos, target_point).convert(inch)) / pow(lookahead_dist.convert(inch), 2);
        double ang_motor_vel = is_using_targetp ? 0 : P_ANG * curvature; // if using target point, then set vel to 0 just in case we go over target point (180_deg ang then.) 

        // ============= Debug ============= 
        if (true && i % 10 == 0) {
            // printf("* Total dist travelled: %f *\n", total_dist_travelled.convert(tile));
            // printf("* MT dist target: %f *\n", mt_profile.dist(elapsed).convert(tile));
            // printf("* Error: %f *\n", (mt_profile.dist(elapsed) - total_dist_travelled).convert(inch));
            printf("* FW: %f *\n", fw_motor_vel/10);
            // printf("* Target vel: %f *\n", mt_profile.vel(elapsed).convert(tps));
            printf("* ang: %f *\n", angle_err.convert(degree));
            //printf("* ANG motor vel: %f *\n", ang_motor_vel);
            // printf("********************\n");
        }
        
        // ============= Move Robot ============= 
        // note that = drive base blue
        drive.moveArcade(
            (fw_motor_vel / 600) * (is_reverse ? -1 : 1),
            ang_motor_vel
        );

        // ============= Check if end program ============= 
        if (
            (elapsed >= (*timeout))
        ) {
            printf("Elapsed time done\n");
            mainLoop = false;
            break;
        }

        if (
            (Math::distance(current_pos, points.end()->point).abs() <= end_tolerance)
        ) {
            printf("Current position and end point less than time tolerance\n");
            mainLoop = false;
            break;
        }

        // ============= Delay ============= 
        pros::delay(10);
        i += 1;
    }

    if (true) { // if debug
        Console::printBrain(8, "Done with movement");
        Control::printController(0, "%f to %f", min_err.convert(inch), max_err.convert(inch));
    }

    drive.moveArcade(0,0); // ensure movement stops at end.

}