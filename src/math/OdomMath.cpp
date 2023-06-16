#include "OdomMath.h"

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
    QLength dist = okapi::OdomMath::computeDistanceToPoint(p2,p1);
    return dist * (okapi::abs(ang) > 90_deg ? -1 : 1);
}


/**
 * @brief Coordinate system is weird in okapi, but we're using it (robot faces in x-direction at first)
 * Note: for some reason if point is directly on it, then the degree is 90...
    * So changed condition so its just... 0 when point is directly on it
 */

QAngle Math::anglePoint(OdomState currentState, Point p1) {
    if (currentState.x - p1.x == 0_in && currentState.y - p1.y == 0_in) { // on same point!
        return 0_deg;
    } else {
        return Math::restrictAngle180(okapi::OdomMath::computeAngleToPoint(p1, currentState));
    }
}

Point Math::findPointOffset(OdomState state, QLength dist) {
    return {
        state.x + okapi::cos(state.theta) * dist,
        state.y + okapi::sin(state.theta) * dist,
    };

}