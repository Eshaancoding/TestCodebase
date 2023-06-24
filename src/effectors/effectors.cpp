#include "effectors.h"

void Effectors::intake(std::int16_t power) {
    intakeMotor.moveVelocity(-power);    
    intakeMotorTwo.moveVelocity(power);
}

void Effectors::outtake(std::int16_t power) {
    intakeMotor.moveVelocity(power);   
    intakeMotorTwo.moveVelocity(-power); 
}

void Effectors::stepCataReset () {
    if (shouldReset) {
        cataMotor.moveVelocity(-128);
        cataMotorTwo.moveVelocity(128);

        if (limitSwitch.get_value() == 1) {
            delay(300_ms);
            cataMotor.moveVelocity(0);
            cataMotorTwo.moveVelocity(0);
            shouldReset = false;
        }
    }
};

void Effectors::shoot() {
    // velocity should be fairly slow
    cataMotor.moveVelocity(-128);
    cataMotorTwo.moveVelocity(128);
    delay(500_ms);
    cataMotor.moveVelocity(0);
    cataMotorTwo.moveVelocity(0);
    shouldReset = true;
}

void Effectors::stopIntake() {
    intakeMotor.moveVelocity(0);
    intakeMotorTwo.moveVelocity(0);
}

void Effectors::delay(QTime time) {
    pros::delay(time.convert(okapi::millisecond));
}

void Effectors::enablePiston() {
    piston.set_value(false);
}

void Effectors::disablePiston() {
    piston.set_value(true);
}