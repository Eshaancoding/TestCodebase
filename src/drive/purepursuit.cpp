#include "drive.h"
#include "odom/Math.h"
#include "odom/OdomCustom.h"

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

    auto d_x = (lineTwo.x - lineOne.x).convert(okapi::inch);
    auto d_y = (lineTwo.y - lineOne.y).convert(okapi::inch);
    auto d_r = sqrt(pow(d_x, 2) + pow(d_y, 2));

    auto d_discrim = lineOne.x.convert(okapi::inch) * lineTwo.y.convert(okapi::inch) - \
                     lineTwo.x.convert(okapi::inch) * lineOne.y.convert(okapi::inch);

    auto discriminant = (pow(lookaheadDistance.convert(okapi::inch), 2) * pow(d_r, 2) - pow(d_discrim, 2));

    if (discriminant < 0) return {}; // there is no points
    else if (discriminant == 0) { // only one point exists
        QLength x = ((d_discrim * d_y) / pow(d_r, 2)) * 1_in;
        QLength y = ((-d_discrim * d_x) / pow(d_r, 2)) * 1_in;
            
        // check whether it's within the points
        if (lineOne.x < x && x < lineTwo.x && lineOne.y < y && y < lineTwo.y)
            return { {x, y} };
        else 
            return {};
    }
    else { // there may exist two points
        vector<Point> pot_points = {};
        
        // find first potential point
        QLength x1 = ((d_discrim * d_y + sign(d_y) * d_x * sqrt(discriminant)) / pow(d_r, 2)) * 1_in;
        QLength y1 = ((-d_discrim * d_x + abs(d_y) * sqrt(discriminant)) / pow(d_r, 2)) * 1_in;
        if (lineOne.x < x1 && x1 < lineTwo.x && lineOne.y < y1 && y1 < lineTwo.y)
            pot_points.push_back({x1, y1});

        // find second potential point
        QLength x2 = ((d_discrim * d_y - sign(d_y) * d_x * sqrt(discriminant)) / pow(d_r, 2)) * 1_in;
        QLength y2 = ((-d_discrim * d_x - abs(d_y) * sqrt(discriminant)) / pow(d_r, 2)) * 1_in;
        if (lineOne.x < x2 && x2 < lineTwo.x && lineOne.y < y2 && y2 < lineTwo.y)
            pot_points.push_back({x2, y2});

        return pot_points;
    }
}

void Drive::goPath (
    std::initializer_list<Path> paths_initializer,
    bool isRelative,
    QLength callbackTol,
    bool isReverse,
    std::optional<QTime> maxTime
) {
    DistancePID.reset();
    HeadingPID.reset();
    
    // =============== First convert all points to absolute if relative =============== 
    // and also convert to vector
    auto current_pos = OdomCustom::getPos();
    if (isReverse) current_pos.theta += 180_deg;
    vector<Path> paths;

    okapi::Point current_point = {current_pos.x, current_pos.y};
    for (int i = 0; i < paths.size(); i++) {
        okapi::Point new_point = (paths.begin()+i)->point;
        if (isRelative) {
            new_point.x += current_point.x;
            new_point.y += current_point.y;
        }
        paths.push_back(Path(
            new_point,
            (paths.begin()+i)->lookaheadDistance,
            (paths.begin()+i)->headingFactor,
            (paths.begin()+i)->distanceFactor,
            (paths.begin()+i)->callback
        ));
        current_point = new_point;
    }

    // factor variables
    int callbackIndexStart = 0;    
    auto start = pros::millis();

    double heading_factor = paths.begin()->headingFactor;
    double distance_factor = paths.begin()->distanceFactor;
    QLength lookaheadDistance = paths.begin()->lookaheadDistance;

    if (lookaheadDistance <= callbackTol)
        throw invalid_argument("Lookahead distance is less than or equal to callback distance");

    // =============== Main while loop =============== 
    bool mainLoop = true;
    while (mainLoop) {
        // get current pos
        current_pos = OdomCustom::getPos();
        if (isReverse) current_pos.theta += 180_deg;
        
        // =============== Set distance/heading/callback ===============
        QLength shortest_distance = -1_in;
        int shortest_index = -1;
        
        for (int i = callbackIndexStart; i < paths.size(); i++) {
            auto path = paths[i];
            auto dist = okapi::abs(Math::distance(current_pos, path.point));
            
            // calculate shortest distance
            if (shortest_distance == -1_in || dist < shortest_distance) {
                shortest_distance = dist;
                shortest_index = i;
            }

            // handle call backs
            if (dist <= callbackTol) {
                if (i == paths.size()-1) {
                    mainLoop = false;
                    break;
                }

                distance_factor = path.distanceFactor;
                heading_factor = path.headingFactor;
                lookaheadDistance = path.lookaheadDistance;

                if (lookaheadDistance <= callbackTol)
                    throw invalid_argument("Lookahead distance is less than or equal to callback distance");

                if (path.callback) (*path.callback)();

                callbackIndexStart++;
                break;
            }
        }


        // =============== Find goal point =============== 
        Point target_point = {0_in, 0_in};
        if (shortest_index == paths.size()-1)
            target_point = paths.end()->point;
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

            if (pot_points.size() == 0)
                throw invalid_argument("No potential points");

            // then, out of all the pot_points, find the one that's closest to the heading point.
            auto heading_point = Math::findPointOffset(current_pos, lookaheadDistance);
            double shortest_distance = -1;
            for (auto p : pot_points) {
                auto d = abs(Math::distance(heading_point, p).convert(okapi::inch));
                if (shortest_distance == -1 || shortest_distance > d) {
                    shortest_distance = d; 
                    target_point = p;
                }
            }
        } 


        // calculate the angle
        double angle_err = Math::anglePoint(current_pos, target_point).convert(okapi::radian);
        double dist_err = abs(Math::distance(current_pos, target_point).convert(okapi::inch));

        // make sure in drive you do the - - if in reverse
        double ang_power = HeadingPID.step(angle_err);
        double dist_power = DistancePID.step(dist_err);

        // Move the robot; uncomment after test
        // drive.moveArcade(
        //     dist_power * (isReverse ? -1 : 1) * distance_factor, 
        //     ang_power * (isReverse ? -1 : 1) * heading_factor
        // );

        // check if we should break the loop if end time tolerance
        if (maxTime && (pros::millis() - start) >= (*maxTime).convert(okapi::millisecond)) {
            mainLoop = false;
            break;
        }

        pros::delay(10);
    }
}