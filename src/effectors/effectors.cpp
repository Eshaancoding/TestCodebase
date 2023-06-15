#include "effectors.h"

void Effectors::intake(std::int16_t power) {
    intakeMotor.moveVelocity(power);
}

void Effectors::outtake(std::int16_t power) {
    intakeMotor.moveVelocity(-power);
}

void Effectors::stopIntake() {
    intakeMotor.moveVelocity(0);
}

void Effectors::spinFlywheel(std::int16_t power) {
    flywheelMotor.moveVelocity(power);
}

void Effectors::stopFlywheel () {
    flywheelMotor.moveVelocity(0);
}

void Effectors::delay(QTime time) {
    pros::delay(time.convert(okapi::millisecond));
}