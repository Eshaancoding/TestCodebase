#include "drive.h"
#include "parameters.h"

void Drive::moveArcade(double distance, double heading) {

    distance *= 600;  // -600 to 600
    heading *= 600;

    // heading = heading > 0 ? log(heading+0.1) + 1 : log(-1*heading+0.1) + 1;
    // leftMotorGroup.moveVelocity(0.95 * (distance + heading));    
    leftMotorGroup.moveVelocity(distance + heading);    
    rightMotorGroup.moveVelocity(distance - heading);
}

void Drive::moveTank (double left, double right) {
    left *= 200; right *= 200;
    leftMotorGroup.moveVelocity(left);     
    rightMotorGroup.moveVelocity(right);   
}