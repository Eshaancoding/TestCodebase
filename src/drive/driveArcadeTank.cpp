#include "drive.h"

void Drive::moveArcade(double distance, double heading) {
    distance *= 600; heading *= 600;
    // leftMotorGroup.moveVelocity(0.95 * (distance + heading));    
    leftMotorGroup.moveVelocity(distance + heading);    
    rightMotorGroup.moveVelocity(distance - heading);
}

void Drive::moveTank (double left, double right) {
    left *= 300; right *= 300;
    leftMotorGroup.moveVelocity(left);     
    rightMotorGroup.moveVelocity(right);   
}