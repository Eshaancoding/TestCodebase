#include "effectors.h"

void Effectors::shoot () {
    cataOne.move_velocity(-600);
    cataTwo.move_velocity(600);
    pros::delay(100);
    while (rotSensor.get_angle() < 3000) {
        pros::delay(50);
    }
    cataOne.move_velocity(0);
    cataTwo.move_velocity(0);
}