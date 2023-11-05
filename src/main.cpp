#include "main.h"
#include "odom/Math.h"
#include "AutonSelector.h"
#include "Console.h"
#include "parameters.h"
#include "effectors.h"
#include "drive.h"
#include "controller.h"
#include "pros/misc.h"
#include "routes.h"

void disabled() {}
void competition_initialize() {}

// Auton Selector wait state function (helper for autonomous and opcontrol)
AutonSelector::State waitForValidState () {
    AutonSelector::State state;
    
    // constantly check state change
    while (true) { 
        auto stateCheck = AutonSelector::getState();             
 
        if (stateCheck.status == AutonSelector::TEST) {
            state = stateCheck;
            break;
        }
        else if (stateCheck.status == AutonSelector::ROUTE) {
            state = stateCheck;
            break;
        }

        pros::delay(200); // doesn't have to check too often :)
    }
    return state;
}

// When robot initializes. 
void initialize() {
    // AutonSelector::init(); 
}

// Autonomous Mode
void autonomous() {
};

// Operation control (driver)

// void opcontrol () {
//     pros::Motor 
// }

// Pistons A - B

void opcontrol() {
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    Drive drive;
    
    okapi::Controller control;
    Effectors eff;

    while (true) {
        double heading = Control::getAnalog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        double distance = Control::getAnalog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

        drive.moveArcade(distance, heading);

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_A)) eff.wingsToggle();
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_B)) eff.intakeToggle();
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_R2)) eff.shootCata();
        eff.resetCata();

        pros::delay(10);
    }
}