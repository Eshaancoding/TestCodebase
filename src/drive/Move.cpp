#include "drive.h"

void Drive::moveArcade (double distance, double heading) {
    distance *= 128; heading *= 128;
    leftMotorGroup.moveVelocity(distance - heading);    // maybe use voltage? 
    rightMotorGroup.moveVelocity(distance + heading);   // maybe use voltage?
}

void Drive::moveTank (double left, double right) {
    left *= 128; right *= 128;
    leftMotorGroup.moveVelocity(left);     // maybe use voltage? 
    rightMotorGroup.moveVelocity(right);   // maybe use voltage?
}