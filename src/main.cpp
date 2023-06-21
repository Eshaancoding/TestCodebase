#include "main.h"
#include "odom/Math.h"
#include "AutonSelector.h"
#include "Console.h"
#include "okapi/impl/device/controller.hpp"
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

};

// Operation control (driver)
void opcontrol() {
    // auto state = waitForValidState();    

    okapi::Controller controller; 

    Console::printBrain(0, "Creating running alg");

    while (true) {
        if (controller.getDigital(okapi::ControllerDigital::A)) {
            effectors.shoot();
        }

        effectors.stepCataReset();
        
        pros::delay(10);
    }
}