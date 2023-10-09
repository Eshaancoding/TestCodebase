#include "effectors.h"

void Effectors::reset () {
    if (state == CataState::RESETTING) {
        cataOne.move_velocity(100);
        cataTwo.move_velocity(-100);
        pros::delay(100);
        while (rotSensor.get_angle() > 15150) {
            pros::delay(5);
            Console::printBrain(4, (double)rotSensor.get_angle(), "Adi shenagains:");
        }
        state = CataState::SHOOTING;
        cataOne.move_velocity(0);
        cataTwo.move_velocity(0);
    }
}

void Effectors::shoot () {
    if (state == CataState::SHOOTING) {
        cataOne.move_velocity(100);
        cataTwo.move_velocity(-100);
        pros::delay(300);
        state = CataState::RESETTING;
    }
}

void Effectors::intake () {
    intakeMotor.move_velocity(-600);
}
void Effectors::resetIntake () {
    intakeMotor.move_velocity(0);
}

