#ifndef MATH_H
#define MATH_H
#include "main.h"
#include "okapi/api/odometry/odomState.hpp"

namespace Math {
    QAngle restrictAngle180 (QAngle angle);
    
    QLength distance (OdomState p1, Point p2);
    QLength distance (Point p1, Point p2);
    QAngle anglePoint (OdomState currentState, Point p1, bool restrict=false);

    Point findPointOffset (OdomState state, QLength dist);
    Point add (okapi::OdomState orig, Point p);

    double sign (double input);

    std::vector<Point> circleLineIntersection (
        Point currentPosition,      // center of circle
        QLength lookaheadDistance,  // radius of circle
        Point lineOne, // line starting point
        Point lineTwo  // line ending point
    );
};

#endif