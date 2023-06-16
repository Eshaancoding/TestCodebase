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

	for (float i = 2.5; i > -2.5; i -= 0.5) {
	
		OdomState p1 = {0.2_in, 0_in, 87_deg};
		Point p2 = {0.1_in, i * 1_in};
	
		printf("Orig P: %f %f %f deg \n", p1.x.convert(inch), p1.y.convert(inch), p1.theta.convert(degree));
		printf("Target P: %f %f \n", p2.x.convert(inch), p2.y.convert(inch));
		printf("Dist: %f\n", 
			Math::distance(p1, p2).convert(okapi::inch)
		);
		printf("Angle: %f\n\n", 
			Math::anglePoint(p1, p2).convert(okapi::degree)
		);
		
		pros::delay(100);

	}
}
