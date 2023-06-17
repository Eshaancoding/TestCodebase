#include "main.h"
#include "OdomMath.h"
#include "AutonSelector/AutonSelector.h"

void disabled() {}
void competition_initialize() {}

// When robot initializes. 
void initialize() {
    AutonSelector::init();
    
}


// Autonomous Mode
void autonomous() {

};

// Operation control (driver)
void opcontrol() {

	Point point = Math::findPointOffset(
		{0_in, 1_in, 180_deg}	
	, 3_in);

	printf("P: %f %f\n", point.x.convert(inch), point.y.convert(inch));
}
