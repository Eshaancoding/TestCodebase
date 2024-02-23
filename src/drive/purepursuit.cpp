#include "drive.h"
#include "odom/Math.h"
#include "odom/OdomCustom.h"
#include "PIDParams.h"

double sign (double x) {
    if (x < 0) return -1;
    else return 1;
}

std::vector<Point> circleLineIntersection (
    Point currentPosition,      // center of circle
    QLength lookaheadDistance,  // radius of circle
    Point lineOne, // line starting point
    Point lineTwo  // line ending point
) {
    const QLength pot_points_tol = 0.1_in;

    // lineOne.x -= currentPosition.x;
    // lineOne.y -= currentPosition.y;

    // lineTwo.x -= currentPosition.x;
    // lineTwo.y -= currentPosition.y;

    auto x1_offset = lineOne.x - currentPosition.x;
    auto y1_offset = lineOne.y - currentPosition.y;

    auto x2_offset = lineTwo.x - currentPosition.x;
    auto y2_offset = lineTwo.y - currentPosition.y;

    auto d_x = (x2_offset - x1_offset).convert(okapi::inch);
    auto d_y = (y2_offset - y1_offset).convert(okapi::inch);
    auto d_r = sqrt(pow(d_x, 2) + pow(d_y, 2));

    auto d_discrim = (x1_offset.convert(okapi::inch) * y2_offset.convert(okapi::inch)) - (x2_offset.convert(okapi::inch) * y1_offset.convert(okapi::inch));

    auto discriminant = (pow(d_r, 2) * pow(lookaheadDistance.convert(okapi::inch), 2))  - pow(d_discrim, 2);

    // find min and max points
    auto minX = min(lineOne.x, lineTwo.x) - pot_points_tol;
    auto maxX = max(lineOne.x, lineTwo.x) + pot_points_tol;

    auto minY = min(lineOne.y, lineTwo.y) - pot_points_tol;
    auto maxY = max(lineOne.y, lineTwo.y) + pot_points_tol;

    if (discriminant < 0) return {}; // there is no points
    else if (discriminant == 0) { // only one point exists
        QLength x = ((d_discrim * d_y) / pow(d_r, 2)) * 1_in;
        QLength y = ((-d_discrim * d_x) / pow(d_r, 2)) * 1_in;
            
        // check whether it's within the points
        auto solX = x + currentPosition.x;
        auto solY = y + currentPosition.y;

        if (minX <= solX && solX <= maxX && minY <= solY && solY <= maxY)
            return { {solX, solY} };
        else 
            return {};
    }
    else { // there may exist two points
        vector<Point> pot_points = {};
        
        // find first potential point
        QLength x1 = ((d_discrim * d_y + sign(d_y) * d_x * sqrt(discriminant)) / pow(d_r, 2)) * 1_in;
        QLength y1 = ((-d_discrim * d_x + abs(d_y) * sqrt(discriminant)) / pow(d_r, 2)) * 1_in;
        Point sol1 = {x1 + currentPosition.x, y1 + currentPosition.y};
        
        // find second potential point
        QLength x2 = ((d_discrim * d_y - sign(d_y) * d_x * sqrt(discriminant)) / pow(d_r, 2)) * 1_in;
        QLength y2 = ((-d_discrim * d_x - abs(d_y) * sqrt(discriminant)) / pow(d_r, 2)) * 1_in;
        Point sol2 = {x2 + currentPosition.x, y2 + currentPosition.y};
        
        // find is between
        if (minX <= sol1.x && sol1.x <= maxX && minY <= sol1.y && sol1.y <= maxY) {
            pot_points.push_back(sol1);
        }
        
        if (minX <= sol2.x && sol2.x <= maxX && minY <= sol2.y && sol2.y <= maxY) {
            pot_points.push_back(sol2);
        }
        
        return pot_points;
    }
}

void Drive::goPath (
    std::initializer_list<Path> paths_initializer,
    QLength callbackTol,
    QLength endTol,
    bool isReverse,
    std::optional<QTime> maxTime
) {
    DistancePID.reset();
    HeadingPID.reset();
    
    // =============== First convert all points to absolute if relative =============== 
    // and also convert to vector
    auto current_pos = OdomCustom::getPos();
    vector<Path> paths = {
        Path(
            {current_pos.x, current_pos.y}, 
            paths_initializer.begin()->lookaheadDistance,
            paths_initializer.begin()->headingFactor,
            paths_initializer.begin()->distanceFactor
        )
    };

    for (int i = 0; i < paths_initializer.size(); i++) {
        okapi::Point new_point = (paths_initializer.begin()+i)->point;
        new_point.x += current_pos.x;
        new_point.y += current_pos.y;
        paths.push_back(Path(
            new_point,
            (paths_initializer.begin()+i)->lookaheadDistance,
            (paths_initializer.begin()+i)->headingFactor,
            (paths_initializer.begin()+i)->distanceFactor,
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
    bool mainLoop = true;
    while (mainLoop) {
        // get current pos
        current_pos = OdomCustom::getPos();
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
                auto result = circleLineIntersection(
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
                mainLoop = false;
                drive.moveArcade(0,0);
                throw invalid_argument("No potential points");
                break;
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
        printf("Current pos %f %f Target point: %f %f callback ind: %d \n", current_pos.x.convert(okapi::tile), current_pos.y.convert(okapi::tile), target_point.x.convert(okapi::tile), target_point.y.convert(okapi::tile), callbackIndexStart);

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

        // Move the robot; uncomment after test
        drive.moveArcade(
            dist_power * distance_factor * (isReverse ? -1 : 1), 
            ang_power * heading_factor * (isReverse ? -1 : 1)
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

        pros::delay(10); //////////////////////////////////////////// TSDKFJSKDFJKSDJFKSJDFKSJDKFJK
    }
    drive.moveArcade(0,0);
}