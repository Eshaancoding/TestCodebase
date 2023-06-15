#include "main.h"
#include "routes.h"

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
	Routes::test();	 // run test just for now
}
