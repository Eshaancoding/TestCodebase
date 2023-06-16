#include "main.h"
#include "OdomMath.h"

void disabled() {}
void competition_initialize() {}

// When robot initializes. 
void initialize() {
	pros::lcd::initialize(); // initialize LCD screen
}


// Autonomous Mode
void autonomous() {

};

// Operation control (driver)
void opcontrol() {
	pros::lcd::print(0, "Hello World!");

	for (float i = -2.5; i < 2.5; i += 0.5) {
		pros::lcd::print(1, "Dist: %f", 
			Math::distance({0_in, 0_in, 0_deg}, {0_in, i*1_in}).convert(okapi::inch)
		);

		pros::lcd::print(2, "Angle: %f", 
			Math::anglePoint({0_in, 0_in, 180_deg}, {0_in, i*1_in}).convert(okapi::degree)
		);
		pros::delay(500);

	}
}
