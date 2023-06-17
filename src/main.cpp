#include "main.h"
#include "OdomMath.h"
#include "BrainScreen/BrainScreen.h"
#include "BrainScreen/Console.h"

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

    Console::printBrain(0, "Hello!");

	Point point = Math::findPointOffset(
		{0_in, 1_in, 180_deg}	
	, 3_in);

    Console::printBrain(0, "P: %f %f \n", point.x.convert(inch), point.y.convert(inch));
    for (int i = 0; i < 100; i++) {
        Console::printBrain(1, "P: %f %f\n", point.x.convert(inch)+i, point.y.convert(inch));
        pros::delay(100);
    }
}
