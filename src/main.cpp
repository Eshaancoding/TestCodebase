#include "main.h"
#include "odom/OdomMath.h"
#include "BrainScreen/AutonSelector.h"
#include "BrainScreen/Console.h"
#include "parameters.h"
#include "pros/rtos.hpp"

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
    for (int i = 0; i < 500; i++) {
        if (i < 30) {
            simulation.step(0.3, 0.1);
            Console::printBrain(2, true, "applied vel");
        } else {
            simulation.step(0, 0);
            Console::printBrain(2, false, "applied vel");
        }

        Console::printBrain(0, simulation.getPos(), "Simulation Pos");
        Console::printBrain(1, simulation.vel, "Velocity");
        

        pros::delay(500);
    }
}