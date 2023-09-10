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
void opcontrol() {
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    Drive drive;
    
    Console::printBrain(1, "Running");
    okapi::Controller control;

    while (true) {
        double heading = Control::getAnalog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        double distance = Control::getAnalog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        
        drive.moveArcade(distance, heading);
        
        // if (Control::getButtonPressed(pros::E_CONTROLLER_DIGITAL_L1)) {
        //     eff.intake();
        // }
        // else {
        //     eff.resetIntake();
        // }

        // if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_A)) {
        //     eff.shoot();
        // }
        // eff.reset();
        
        // if (control.getDigital(okapi::ControllerDigital::A)) {
        //     Console::printBrain(0, "Digital press");
        //     eff.cataOne.move_velocity(-200);
        //     eff.cataTwo.move_velocity(200);
        // }
        // else {
        //     Console::printBrain(0, "Digital not press");
        //     eff.cataOne.move_velocity(0);
        //     eff.cataTwo.move_velocity(0);
        // }
        

        pros::delay(10);
    }


}