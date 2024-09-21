#include "drive.h"

void Drive::moveArcade(double distance, double heading) {
    distance *= 200; heading *= 200;
    // leftMotorGroup.moveVelocity(0.95 * (distance + heading));    
    leftMotorGroup.moveVelocity(distance + heading);    
    rightMotorGroup.moveVelocity(distance - heading);
}

void Drive::moveTank (double left, double right) {
    left *= 200; right *= 200;
    leftMotorGroup.moveVelocity(left);     
    rightMotorGroup.moveVelocity(right);   
}