#include "Odom/Math.h"

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

/**
 * 
 */

QAngle Math::anglePoint(OdomState currentState, Point p1, bool restrict) {
    QLength xDiff = p1.x - currentState.x;
    QLength yDiff = p1.y - currentState.y;
    if (xDiff == 0_in && yDiff == 0_in) { // on same point!
        return 0_deg;
    } else {
        auto ang = Math::restrictAngle180(okapi::atan2(yDiff, xDiff) - currentState.theta);

        if (!restrict) return ang;

        if (okapi::abs(ang) > 90_deg) 
            return (180_deg - okapi::abs(ang)) * (ang < 0_deg ? 1 : -1);
        else 
            return ang;
    }
}

Point Math::findPointOffset(OdomState state, QLength dist) {
    return {
        state.x + okapi::cos(state.theta) * dist,
        state.y + okapi::sin(state.theta) * dist,
    };

}