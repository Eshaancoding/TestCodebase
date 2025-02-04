#include "okapi/api/odometry/odomMath.hpp"
#include "Odom/Math.h"
#include "Console.h"

QAngle Math::restrictAngle180(QAngle angle) {
    // >= 180, goes negative (-180)
    // supports for angles > 360
    return okapi::OdomMath::constrainAngle180(angle);
}

/**
 * @brief Returns the distance between point by point
 * reports negative distance if the odomstate (p1) is PAST the p2 (this is useful for PID stuff)
*/
QLength Math::distance(OdomState p1, Point p2) {
    QAngle ang = anglePoint(p1, p2);
    double xDiff = (p2.x - p1.x).convert(okapi::inch);
    double yDiff = (p2.y - p1.y).convert(okapi::inch);
    QLength dist = sqrt(pow(xDiff, 2) + pow(yDiff, 2)) * 1_in;
    return dist * (okapi::abs(ang) > 150_deg ? -1 : 1);
}

QLength Math::distance (Point p1, Point p2) {
    double xDiff = (p2.x - p1.x).convert(okapi::inch);
    double yDiff = (p2.y - p1.y).convert(okapi::inch);
    QLength dist = sqrt(pow(xDiff, 2) + pow(yDiff, 2)) * 1_in;
    return dist;
}

/**
 * computes the difference in angle between target point and current robot position (along with theta)
 */

QAngle Math::anglePoint(OdomState currentState, Point p1, bool restrict) {
    QLength xDiff = p1.x - currentState.x; // 0
    QLength yDiff = p1.y - currentState.y; // 20
    if (xDiff == 0_in && yDiff == 0_in) { // on same point!
        return 0_deg;
    } else {
        auto ang = Math::restrictAngle180(okapi::atan2(xDiff, yDiff) - currentState.theta);

        if (!restrict) return ang;

        if (okapi::abs(ang) > 160_deg) 
            return (180_deg - okapi::abs(ang)) * (ang < 0_deg ? 1 : -1);
        else 
            return ang;
    }
}

Point Math::findPointOffset(OdomState state, QLength dist) {
    
    return {
        state.x + okapi::sin(state.theta) * dist,
        state.y + okapi::cos(state.theta) * dist,
    };
}

Point Math::add (okapi::OdomState orig, Point p) {
    p.x += orig.x;
    p.y += orig.y;
    return p; 
}

double Math::sign (double x) {
    if (x < 0) return -1;
    else return 1;
}

std::vector<Point> Math::circleLineIntersection (
    Point currentPosition,      // center of circle
    QLength lookaheadDistance,  // radius of circle
    Point lineOne, // line starting point
    Point lineTwo  // line ending point
) {
    const QLength pot_points_tol = 0.1_in;

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