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

        pros::delay(50);
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
    drive.turnRight(90_deg, {}, {
        {0.3, []() { Console::printBrain(7, "0.3 done"); } },
        {0.6, []() { Console::printBrain(7, "0.6 done"); } }
    });
}