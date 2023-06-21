#include "effectors.h"

void Effectors::intake(std::int16_t power) {
    intakeMotor.moveVelocity(power);    // might be reverse
    intakeMotorTwo.moveVelocity(-power);// might be reverse
}

void Effectors::outtake(std::int16_t power) {
    intakeMotor.moveVelocity(-power);   // might be reverse
    intakeMotorTwo.moveVelocity(power); // might be reverse
}

void Effectors::stepCataReset () {
    if (shouldReset) {
        Console::printBrain(2, "Resetting...");
        cataMotor.moveVelocity(-128);
        cataMotorTwo.moveVelocity(128);

        if (limitSwitch.get_value() == 1) {
            cataMotor.moveVelocity(0);
            cataMotorTwo.moveVelocity(0);
            shouldReset = false;
            Console::printBrain(2, "Stop limit switch");
        }
    }
};

void Effectors::shoot() {
    // velocity should be fairly slow
    Console::printBrain(2, "starting shoting");
    cataMotor.moveVelocity(-128);
    cataMotorTwo.moveVelocity(128);
    delay(500_ms);
    cataMotor.moveVelocity(0);
    cataMotorTwo.moveVelocity(0);
    shouldReset = true;
    Console::printBrain(2, "Cata motor shooting ");
}

void Effectors::stopIntake() {
    intakeMotor.moveVelocity(0);
    intakeMotorTwo.moveVelocity(0);
}

void Effectors::delay(QTime time) {
    pros::delay(time.convert(okapi::millisecond));
}