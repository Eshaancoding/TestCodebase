#ifndef MATH_H
#define MATH_H
#include "main.h"

namespace Math {
    QAngle restrictAngle360 (QAngle angle);
    QAngle restrictAngle180 (QAngle angle);
    
    QLength distanceForm (Point p1, Point p2);
    QLength distanceForm (OdomState p1, Point p2);
    QAngle anglePoint (OdomState currentState, Point p1);

    Point findPointOffset (OdomState state, QLength dist);
};

#endif