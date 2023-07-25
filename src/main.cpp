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
    effectors.reset();
}

// Autonomous Mode
void autonomous() {
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    Routes::left();
};

// Operation control (driver)
void opcontrol() {
    // ******************** DRIVE CODE ***************
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);

    while (true) {
        double analogLeft = Control::getAnalog(E_CONTROLLER_ANALOG_LEFT_Y);
        double analogRight = Control::getAnalog(E_CONTROLLER_ANALOG_RIGHT_X);

        drive.moveArcade(analogLeft, analogRight);

    } 
}