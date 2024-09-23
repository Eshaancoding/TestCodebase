#include "effectors.h"
#include "parameters.h"
#include "controller.h"
#include "drive.h"
#include <cstdarg>

void Effectors::toggleArm(){ //PRAC code
    /*
    armActive = !armActive;
    arm.move_velocity(armActive ? -100 : 100); //ask
    pros::delay(10000); //10 seconds
    arm.move_velocity(0);
    */
}

// INTAKE
void Effectors::setIntakeState (IntakeState ia, bool isConveyor) {
    if (ia == this->intakeActive) { // toggle!
        intakeMotor.move_velocity(0);
        if (isConveyor)
            conveyorMotor.move_velocity(0);
        this->intakeActive = IntakeState::INACTIVE;
        return; // don't do anything else
    }

    if (ia == IntakeState::OUTTAKE) {
        intakeMotor.move_velocity(200);
        if (isConveyor)
            conveyorMotor.move_velocity(200);
        
    }
    // COMMENT THIS OUT IF YOU WANT TO STEP OUTTAKE AND LISTEN TO LIMIT SWITCH
    else if (ia == IntakeState::INTAKE) {  
        intakeMotor.move_velocity(-200);
        if (isConveyor)
            conveyorMotor.move_velocity(-200);
    }
    else if (ia == IntakeState::INACTIVE) {
        intakeMotor.move_velocity(0);
        if (isConveyor)
            conveyorMotor.move_velocity(0);
    }
    
    this->intakeActive = ia;
}

void Effectors::intakeToggle (bool reverse) {
    if (intakeActive == IntakeState::INTAKE && reverse) { // intake --> want to reverse --> reverse 
        intakeMotor.move_velocity(-200);
        conveyorMotor.move_velocity(-200);
        intakeActive = IntakeState::OUTTAKE;
    } 
    else if (intakeActive == IntakeState::OUTTAKE && !reverse) { // outtake --> want to intake --> intake
        //intakeMotor.move_velocity(200);
        //conveyorMotor.move_velocity(200);
        intakeActive = IntakeState::INTAKE;
    }
    else if (intakeActive == IntakeState::INACTIVE) {
        intakeMotor.move_velocity(200 * (reverse ? 0 : 1)); // change to -1
        conveyorMotor.move_velocity(200* (reverse ? 0 : 1)); // change to -1
        intakeActive = reverse ? IntakeState::OUTTAKE : IntakeState::INTAKE;
    }
    else if ((intakeActive == IntakeState::INTAKE && !reverse) || 
             (intakeActive == IntakeState::OUTTAKE && reverse))
    {
        intakeMotor.move_velocity(0);
        conveyorMotor.move_velocity(0);
        intakeActive = IntakeState::INACTIVE;
    }

    if (intakeActive != IntakeState::OUTTAKE) {
        first_click = false;
        previous_limit = 0;
    }

}

void Effectors::stepOuttake () {
    // inside a while true loop!
    if (intakeActive == IntakeState::OUTTAKE) {
        bool val = limitSwitch.get_value();
        
        if (val && !previous_limit) { // debounce function
            if (first_click) {
                conveyorMotor.move_velocity(-200);
            }
            
            first_click = !first_click; 
        }

        previous_limit = val;
    }
    

}

void Effectors::setIntake (bool isReverse, bool isOff) {
    float powOne = (isReverse ? 1 : -1) * !isOff * 12000;
    float powTwo = (isReverse ? -1 : 1) * !isOff * 12000;
    intakeMotor.move_voltage(powOne);

    if (isOff)          intakeActive = IntakeState::INACTIVE;
    else if (isReverse) intakeActive = IntakeState::OUTTAKE;
    else                intakeActive = IntakeState::INTAKE;
}

void Effectors::toggleClamp(){
    isClamped = !isClamped;
    clampPistonLeft.set_value(isClamped);
    // clampPistonRight.set_value(isClamped);
}

void Effectors::raiseArm () {
    arm.move_voltage(8000);
}

void Effectors::lowerArm () {
    arm.move_voltage(-8000);
}

void Effectors::stopArm () {
    arm.move_velocity(0);
}

void Effectors::toggleBoinker () {
    boinkerActive = !boinkerActive;
    boinkerPiston.set_value(boinkerActive);
}