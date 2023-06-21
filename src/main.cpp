#include "main.h"
#include "odom/Math.h"
#include "AutonSelector.h"
#include "Console.h"
#include "okapi/impl/device/controller.hpp"
#include "okapi/impl/device/controllerUtil.hpp"
#include "parameters.h"
#include "effectors.h"
#include "drive.h"

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
    auto state = waitForValidState();    
};

// Operation control (driver)
void opcontrol() {

    okapi::Controller controller; 

    while (true) {
        double analogLeft = controller.getAnalog(okapi::ControllerAnalog::leftY);
        double analogRight = controller.getAnalog(okapi::ControllerAnalog::rightY);

        drive.moveTank(analogLeft, analogRight);

        if (controller.getDigital(okapi::ControllerDigital::L1)) {
            effectors.shoot();
        }

        if (controller.getDigital(okapi::ControllerDigital::R1)) {
            effectors.intake(127);
        }
        else if (controller.getDigital(okapi::ControllerDigital::R2)) {
            effectors.outtake(127);
        }
        else {
            effectors.stopIntake();
        }

        effectors.stepCataReset();

        Console::printBrain(2, odometery.getPos(), "Pos");
        
        pros::delay(10);
    }
}