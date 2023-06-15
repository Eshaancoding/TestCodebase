#include "main.h"

void disabled() {}
void competition_initialize() {}

// When robot initializes. 
void initialize() {
	pros::lcd::initialize(); // initialize LCD screen
}


// Autonomous Mode
void autonomous() {};

// Operation control (driver)
void opcontrol() {
	pros::lcd::print(0, "Hello World!");
}
