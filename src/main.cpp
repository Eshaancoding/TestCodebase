#include "main.h"
#include "odom/Math.h"
#include "AutonSelector.h"
#include "Console.h"
#include "parameters.h"
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
    AutonSelector::init(); 
}

// Autonomous Mode
void autonomous() {

};

// Operation control (driver)
void opcontrol() {
    auto state = waitForValidState();    

    if (state.status == AutonSelector::TEST) {
        Console::printBrain(6, "Facing 1, 1");
        drive.faceToPoint({1_in, 1_in}, true);
        Console::printBrain(6, "Going 1, 1");
        drive.goToPoint({1_tile, 1_tile}, true);
        
        Console::printBrain(6, "Facing -1, -1");
        drive.faceToPoint({-1_in, -1_in}, true);
        Console::printBrain(6, "Going 0, 0");
        drive.goToPoint({0_in, 0_in}, false);
    }
}