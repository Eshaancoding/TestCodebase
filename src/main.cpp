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
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    Effectors eff;

    while (true) {
        // if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_A)) {
        //     eff.shoot();
        // }
        if (Control::getButtonPressed(pros::E_CONTROLLER_DIGITAL_A)) {
            eff.cataOne.move_velocity(-600);
            eff.cataTwo.move_velocity(600);
        }
        else {
            eff.cataOne.move_velocity(0);
            eff.cataTwo.move_velocity(0);
        }
        Control::printController(0, "Val: %f", (float)eff.rotSensor.get_angle());
        

        pros::delay(10);
    }

};

// Operation control (driver)
void opcontrol() {
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    // Routes::left();
}