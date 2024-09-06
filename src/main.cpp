#include "main.h"
#include "odom/Math.h"
#include "AutonSelector.h"
#include "Console.h"
#include "parameters.h"
#include "effectors.h"
#include "drive.h"
#include "controller.h"
#include "odom/OdomCustom.h"
#include "pros/misc.h"
#include "routes.h"

void disabled() {}
void competition_initialize() {}

/*
*************************************************************
Hi adi if you want an intro to the codebase,
you could head up to the README I documented some stuff
*************************************************************
*/

// Auton Selector wait state function (helper for autonomous and opcontrol)
AutonSelector::State waitForValidState () {
    AutonSelector::State state;
    
    // constantly check state change
    while (true) { 
        auto stateCheck = AutonSelector::getState();             
        auto isCalibrating = OdomCustom::isCalibrating();
 
        if (stateCheck.status == AutonSelector::SKILL && !isCalibrating) {
            state = stateCheck;
            break;
        }
        else if (stateCheck.status == AutonSelector::ROUTE && !isCalibrating) {
            state = stateCheck;
            break;
        }

        pros::delay(200); // doesn't have to check too often :)
    }
    return state;
}

// When robot initializes. 
void initialize() {
    AutonSelector::init();

    leftMotorGroup.setGearing(AbstractMotor::gearset::blue);
    rightMotorGroup.setGearing(AbstractMotor::gearset::blue);
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);

    drive.resetToleranceParams();
    //OdomCustom::init(); 
    //Task task (OdomCustom::MainLoop);

}

// Autonomous Mode
void autonomous() {
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    
    // drive.goForward(2_tile);
    // drive.turnRight(135_deg);
    // Routes::skills();
    // Routes::qualOffensive();
    
    // auto state = waitForValidState();     
    // if (state.status == AutonSelector::SKILL)
    //     Routes::new_skills();
    // else if (state.elimQualState == AutonSelector::ElimQualState::ELIM && state.offDefState == AutonSelector::OffDefState::DEFENSIVE) 
    //     Routes::sixBall();
    // else if (state.elimQualState == AutonSelector::ElimQualState::ELIM && state.offDefState == AutonSelector::OffDefState::OFFENSIVE) 
    //     Routes::qualDefensive();
    // else if (state.elimQualState == AutonSelector::ElimQualState::QUAL && state.offDefState == AutonSelector::OffDefState::DEFENSIVE) 
    //     Routes::qualDefensive();
    // else if (state.elimQualState == AutonSelector::ElimQualState::QUAL && state.offDefState == AutonSelector::OffDefState::OFFENSIVE) 
    //     Routes::qualOffensive();

    // drive.goForward(2_tile);
    // drive.goBackward(1_tile);
    
    // going backward
    // Routes::new_skills();
};

// you disabled the factor map thing

void opcontrol() {
    bool isShooting = false;    
    bool isPTOEnabled = false;
    bool isIntaking = false;

    // ================== COAST ================== 
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);

    while (true) {
        // ======================== Arcade ======================== 
        double heading =  Control::getAnalog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        double distance = Control::getAnalog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

        // ======================== Tank ======================== 
        // double left = Control::getAnalog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        // double right = Control::getAnalog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        drive.moveArcade(distance, heading);

        // if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_LEFT))
        //     eff.toggleDriveReverse();

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_L1))
            eff.intakeToggle();

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_L2))
            eff.intakeToggle(true);

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_X))
            eff.toggleClamp();           

        if (Control::getButtonPressed(pros::E_CONTROLLER_DIGITAL_R1))
            eff.raiseArm();
        else if (Control::getButtonPressed(pros::E_CONTROLLER_DIGITAL_R2))
            eff.lowerArm();
        else
            eff.stopArm();

        pros::delay(10);
    }
}

// R2: macro to go up and PTO and shit. Make sure you go back down.
// L1: wings
// L2: move intake (no outtake)
// R1: Shooting (adi wants some fancy shit)

/*PRAC code
void vroom(int vel){
  rightMotorGroup.moveVelocity(vel); //vel -127 to 127
  pros::delay(10); //in ms
  rightMotorGroup.moveVelocity(0);
}
*/