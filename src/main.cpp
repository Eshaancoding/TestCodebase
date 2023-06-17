#include "main.h"
#include "OdomMath.h"
#include "BrainScreen/AutonSelector.h"
#include "BrainScreen/Console.h"

void disabled() {}
void competition_initialize() {}

// When robot initializes. 
void initialize() {
    AutonSelector::init(); 
}


// Autonomous Mode
void autonomous() {
    while (true) {
        auto state = AutonSelector::getState();

        if (state.status == AutonSelector::NOTREADY) {
            Console::printBrain(0, "Auton READY!");
        } 
        else if (state.status == AutonSelector::TEST) {
            Console::printBrain(0, "Auton TEST!");
        }
        else if (state.status == AutonSelector::ROUTE) {
            Console::printBrain(0, "Auton ROUTE!");
        }

        pros::delay(10);
    }

};

// Operation control (driver)
void opcontrol() {


    while (true) {
        auto state = AutonSelector::getState();

        if (state.status == AutonSelector::NOTREADY) {
            Console::printBrain(0, "Op READY!");
        } 
        else if (state.status == AutonSelector::TEST) {
            Console::printBrain(0, "Op TEST!");
        }
        else if (state.status == AutonSelector::ROUTE) {
            Console::printBrain(0, "Op ROUTE!");
        }

        pros::delay(10);
    }
}
