#include "Console.h"
#include "drive.h"
#include "Odom/Math.h"
#include "odom/OdomCustom.h"
#include "okapi/api/odometry/odomState.hpp"
#include "okapi/api/units/QAcceleration.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QSpeed.hpp"
#include "parameters.h"
#include "odom/OdomArc.h"
#include "pros/rtos.h"
#include <cmath>

void Drive::move (
    std::initializer_list<DrivePoint> points,
    QLength point_tolerance
) {
    // ======= Convert points into bezier curve ======= 

    // ============= Setup Main Loop ============= 
    DistancePID.reset();
    HeadingPID.reset();

    QLength lookahead_dist = points.begin()->lookaheadDistance; 
    int pointIdx = 0; // last point that we hit

    auto start = pros::c::millis();
    bool mainLoop = true;
    bool is_reverse = Math::anglePoint(OdomCustom::getPos(), (points.begin()+1)->point) > 90_deg;

    // ============= Main Loop ============= 
    while (mainLoop) {

        // ============= Get current conditions ============= 
        auto elapsed_sec = double(pros::c::millis() - start) / 1000;
        auto current_pos = OdomArc::getPos();

        // ======== Set lookahead distance and call callback ======
        // max speed, acceleration, and curvature speed are accounted for throughout the path in motion profiling 
        for (int i = pointIdx; i < points.size(); i++) {
            auto drive_point = *(points.begin() + i);
            if (Math::distance(current_pos, drive_point.point) <= point_tolerance) {
                lookahead_dist = drive_point.lookaheadDistance;
                if (drive_point.callback) (*drive_point.callback)();
                pointIdx++;
                break;
            }
        }

        // ============= Calculate the motion profiling ============= 

    
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

        // find angle error
        QAngle angle_err = Math::anglePoint(current_pos, target_point);

        // ============= Delay ============= 
        pros::delay(10);
    }

    drive.moveArcade(0,0); // ensure movement stops at end.

}