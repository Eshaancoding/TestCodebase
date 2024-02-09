#ifndef MATH_H
#define MATH_H
#include "main.h"

namespace Math {
    QAngle restrictAngle180 (QAngle angle);
    
    QLength distance (OdomState p1, Point p2);
    QLength distance (Point p1, Point p2);
    QAngle anglePoint (OdomState currentState, Point p1, bool restrict=false);

    Point findPointOffset (OdomState state, QLength dist);
};

#endif