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

	Point point = Math::findPointOffset(
		{0_in, 1_in, 180_deg}	
	, 3_in);

	printf("P: %f %f", point.x.convert(inch), point.y.convert(inch));
}
