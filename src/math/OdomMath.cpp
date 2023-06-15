#include "OdomMath.h"

QAngle Math::restrictAngle180(QAngle angle) {
    return okapi::OdomMath::constrainAngle180(angle); // <-- ehh much rather do this manually but we'll see
}

QAngle Math::restrictAngle360(QAngle angle) {
    return okapi::OdomMath::constrainAngle360(angle); // <-- ehh much rather do this manually but we'll see
}

QLength Math::distanceForm(Point p1, Point p2) {
    return okapi::OdomMath::computeDistanceToPoint(p1, {p2.x, p2.y, 0_deg}); // why we need theta :/
}

QLength Math::distanceForm(OdomState p1, Point p2) {
    return okapi::OdomMath::computeDistanceToPoint(p2,p1); // hopefully gives negative values based on odom state deg? hopefullysdfsdf
}

QAngle Math::anglePoint(OdomState currentState, Point p1) {
    return okapi::OdomMath::computeAngleToPoint(p1, currentState); // <-- ehh much rather do this manually be we'll see
}

Point Math::findPointOffset(OdomState state, QLength dist) {
    return {
        state.x + okapi::cos(state.theta) * dist,
        state.y + okapi::sin(state.theta) * dist,
    };

    // kind of suspicious of okapi::sin... (180? 360? etc.)
}