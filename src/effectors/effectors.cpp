#include "effectors.h"
#include "parameters.h"
#include "controller.h"
#include "drive.h"

void Effectors::toggleArm(){ //PRAC code
    /*
    armActive = !armActive;
    arm.move_velocity(armActive ? -100 : 100); //ask
    pros::delay(10000); //10 seconds
    arm.move_velocity(0);
    */
}

// INTAKE
void Effectors::intakeToggle (bool reverse) {
    float reverseFactor = 1;
    if (intakeActive == IntakeState::INTAKE && reverse) {
        reverseFactor = -1; 
        intakeMotor.move_velocity(200 * reverseFactor);
        intakeActive = IntakeState::OUTTAKE;
        conveyorMotor.move_velocity(200*reverseFactor);
    } 
    else if (intakeActive == IntakeState::OUTTAKE && !reverse) {
        reverseFactor = 1;
        intakeMotor.move_velocity(-200 * reverseFactor);
        conveyorMotor.move_velocity(-200*reverseFactor);
        intakeActive = IntakeState::INTAKE;
    }
    else if (intakeActive == IntakeState::INACTIVE) {
        reverseFactor = reverse ? -1 : 1; 
        intakeMotor.move_velocity(200 * reverseFactor);
        conveyorMotor.move_velocity(200*reverseFactor);
        intakeActive = reverse ? IntakeState::OUTTAKE : IntakeState::INTAKE;
    }
    else if ((intakeActive == IntakeState::INTAKE && !reverse) || 
             (intakeActive == IntakeState::OUTTAKE && reverse))
    {
        intakeMotor.move_velocity(0);
        intakeActive = IntakeState::INACTIVE;
        conveyorMotor.move_velocity(0);
    }
}

void Effectors::setIntake (bool isReverse, bool isOff) {
float powOne = (isReverse ? 1 : -1) * !isOff * 12000;
    float powTwo = (isReverse ? -1 : 1) * !isOff * 12000;
    intakeMotor.move_voltage(powOne);
}

void Effectors::toggleClamp(){
    isClamped = !isClamped;
    clampPistonLeft.set_value(isClamped);
    clampPistonRight.set_value(isClamped);
}

void Effectors::raiseArm () {
    arm.move_velocity(200);
}

void Effectors::lowerArm () {
    arm.move_voltage(-6000);
}

void Effectors::stopArm () {
    arm.move_velocity(0);
}