#include "drive.h"
#include "odom/Math.h"
#include "odom/OdomArc.h"
#include "PIDParams.h"

void Drive::goPathDepr (
    std::initializer_list<PathDepr> paths_initializer,
    QLength callbackTol,
    QLength endTol,
    bool isReverse,
    std::optional<QTime> maxTime
) {
    DistancePID.reset();
    HeadingPID.reset();
    
    // =============== First convert all points to absolute if relative =============== 
    // and also convert to vector
    auto current_pos = OdomArc::getPos();
    vector<PathDepr> paths;

    for (int i = 0; i < paths_initializer.size(); i++) {
        okapi::Point new_point = (paths_initializer.begin()+i)->point;
        new_point.x += current_pos.x;
        new_point.y += current_pos.y;
        paths.push_back(PathDepr(
            new_point,
            (paths_initializer.begin()+i)->headingFactor,
            (paths_initializer.begin()+i)->distanceFactor,
            (paths_initializer.begin()+i)->lookaheadDistance,
            (paths_initializer.begin()+i)->callback
        ));
    }

    // factor variables
    int callbackIndexStart = 0;    
    auto start = pros::millis();

    double heading_factor = paths.begin()->headingFactor;
    double distance_factor = paths.begin()->distanceFactor;
    QLength lookaheadDistance = paths.begin()->lookaheadDistance;

    // =============== Main while loop =============== 
    int iteration = 0;
    bool mainLoop = true;
    while (mainLoop) {
        iteration++;
        // get current pos
        current_pos = OdomArc::getPos();
        current_pos.theta += (isReverse ? 180_deg : 0_deg);
        
        // =============== Set distance/heading/callback ===============
        for (int i = callbackIndexStart; i < paths.size(); i++) {
            auto path = paths[i];
            auto dist = okapi::abs(Math::distance(current_pos, path.point));
            
            // handle call backs
            if (dist <= callbackTol) {
                distance_factor = path.distanceFactor;
                heading_factor = path.headingFactor;
                lookaheadDistance = path.lookaheadDistance;

                if (path.callback) (*path.callback)();

                callbackIndexStart++;
                Console::printBrain(1, i, "Called callback: ");
                break;
            }
        }

        Console::printBrain(0, "Okay main loop...");

        // =============== Find goal point =============== 
        Point target_point = {0_in, 0_in};
        if (callbackIndexStart == paths.size()-1) // this is... kinda sketchy?
            target_point = (paths.begin()+(paths.size()-1))->point;
        else {
            vector<Point> pot_points = {};
            
            // find circle line intersection
            for (int x = 0; x < paths.size()-1; x++) {
                auto result = Math::circleLineIntersection(
                    {current_pos.x, current_pos.y},
                    lookaheadDistance,
                    (paths.begin()+x)->point,
                    (paths.begin()+x+1)->point
                );
                if (result.size() == 1) pot_points.push_back(result[0]);
                if (result.size() == 2) {
                    pot_points.push_back(result[0]);
                    pot_points.push_back(result[1]);
                }
            }

            if (pot_points.size() == 0) {
                // mainLoop = false;
                // drive.moveArcade(0,0);
                // throw invalid_argument("No potential points");
                continue;
            }

            // then, out of all the pot_points, find the one that's closest to the heading point.
            auto heading_point = Math::findPointOffset(current_pos, lookaheadDistance);

            double shortest_distance = -1;
            for (auto p : pot_points) {
                auto d = abs(Math::distance(heading_point, p).convert(okapi::inch));
                if (shortest_distance == -1 || d < shortest_distance) {
                    shortest_distance = d; 
                    target_point = p;
                }
            }
        } 

        Console::printBrain(2, current_pos, "current pos");
        Console::printBrain(3, target_point, "target point");

        // calculate the angle
        double angle_err = Math::anglePoint(current_pos, target_point).convert(okapi::radian);
        double dist_err = Math::distance(current_pos, target_point).convert(okapi::inch);

        if (dist_err > LOOKAHEAD_DIST.convert(okapi::inch)) dist_err = LOOKAHEAD_DIST.convert(okapi::inch);
        if (dist_err < -LOOKAHEAD_DIST.convert(okapi::inch)) dist_err = -LOOKAHEAD_DIST.convert(okapi::inch);

        // make sure in drive you do the - - if in reverse
        double ang_power = HeadingPID.step(angle_err);
        double dist_power = DistancePID.step(dist_err);

        Console::printBrain(4, dist_err, "dist err: ");
        Console::printBrain(5, angle_err, "angle err: ");
        Console::printBrain(6, dist_power, "raw dist power: ");
        Console::printBrain(7, ang_power, "raw ang power: ");
        if (iteration % 2 == 0) {
            printf("c: %f %f t: %f %f callback: %d head: %f dist: %f dist_pow: %f ang_pow: %f \n", 
                current_pos.x.convert(okapi::tile), 
                current_pos.y.convert(okapi::tile), 
                target_point.x.convert(okapi::tile), 
                target_point.y.convert(okapi::tile), 
                callbackIndexStart, 
                heading_factor, 
                distance_factor,
                dist_power,
                ang_power
            );
        }

        // Move the robot; uncomment after test
        drive.moveArcade(
            dist_power * distance_factor * (isReverse ? -1 : 1), 
            ang_power * heading_factor
        );

        // check if we should break the loop if end time tolerance
        if (maxTime && (pros::millis() - start) >= (*maxTime).convert(okapi::millisecond)) {
            mainLoop = false;
            break;
        }

        // or check if whether close to last point
        if (abs(Math::distance(current_pos, (paths.begin()+(paths.size()-1))->point).convert(okapi::inch)) < endTol.convert(okapi::inch)) {
            mainLoop = false;
            break;
        }

        pros::delay(10);
    }
    drive.moveArcade(0,0);
}