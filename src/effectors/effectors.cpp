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
    float reverseFactor = 1;
    if (intakeActive == IntakeState::INTAKE && reverse) {
        reverseFactor = -1; 
        intakeMotor.move_velocity(intakeActive ? -600 * reverseFactor : 0);
        intakeMotorTwo.move_velocity(intakeActive ? 600 * reverseFactor : 0);
        intakeActive = IntakeState::OUTTAKE;
    } 
    else if (intakeActive == IntakeState::OUTTAKE && !reverse) {
        intakeMotor.move_velocity(intakeActive ? -600 * reverseFactor : 0);
        intakeMotorTwo.move_velocity(intakeActive ? 600 * reverseFactor : 0);
        intakeActive = IntakeState::INTAKE;
    }
    else if (intakeActive == IntakeState::INACTIVE) {
        reverseFactor = reverse ? -1 : 1; 
        intakeMotor.move_velocity(intakeActive ? -600 * reverseFactor : 0);
        intakeMotorTwo.move_velocity(intakeActive ? 600 * reverseFactor : 0);
        intakeActive = reverse ? IntakeState::OUTTAKE : IntakeState::INTAKE;
    }
    else if ((intakeActive == IntakeState::INTAKE && !reverse) || 
             (intakeActive == IntakeState::OUTTAKE && reverse))
    {
        intakeMotor.move_velocity(0);
        intakeMotorTwo.move_velocity(0);
        intakeActive = IntakeState::INACTIVE;
    }
}

void Effectors::setIntake (bool isReverse, bool isOff) {
    float powOne = (isReverse ? 1 : -1) * !isOff * 600;
    float powTwo = (isReverse ? -1 : 1) * !isOff * 600;
    intakeMotor.move_velocity(powOne);
    intakeMotorTwo.move_velocity(powTwo);
}