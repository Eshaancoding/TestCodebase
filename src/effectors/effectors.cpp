#include "effectors.h"

// CATAPAULT
void Effectors::resetCata () {
    if (state == CataState::RESETTING) {
        if (rotSensor.get_angle() > 15000) {
            cataOne.move_velocity(100);
            cataTwo.move_velocity(-100);
        } else {
            state = CataState::SHOOTING;
            cataOne.move_velocity(0);
            cataTwo.move_velocity(0);
        }
    }
}

void Effectors::shootCata () {
    if (state == CataState::SHOOTING) {
        cataOne.move_velocity(100);
        cataTwo.move_velocity(-100);
        pros::delay(300);
        state = CataState::RESETTING;
    }
}

// WINGS
void Effectors::wingsToggle () {
    wingsActive = !wingsActive;
    piston.set_value(wingsActive); // there's a get value here in piston
}

// INTAKE
void Effectors::intakeToggle (bool reverse) {
    if (reverse) {
        intakeMotor.move_velocity(600);
        intakeMotorTwo.move_velocity(-600);
    } else {
        intakeActive = !intakeActive;
        intakeMotor.move_velocity(intakeActive ? -600  : 0);
        intakeMotorTwo.move_velocity(intakeActive ? 600 : 0);
    }
}