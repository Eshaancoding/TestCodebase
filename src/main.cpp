#include "main.h"
#include "odom/OdomMath.h"
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
        drive.turnRight(90_deg);
        drive.goForward(2_tile);
        drive.turnLeft(45_deg);
        drive.goBackward(4_tile);

        Console::printBrain(8, simulation.getPos(), "Final Pos");
    }
}