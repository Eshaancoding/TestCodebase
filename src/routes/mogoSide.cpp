#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

// RELEASE MOGO 1 AFTER YOU GO MORE INWARDS TO YOU

void Routes::mogoSide () {

	OdomArc::setPos(5.7283_tile, 1.7115_tile, 1_deg);

	eff.toggleBoinker();

	drive.goForward(1.65_tile);

	drive.goBackward(0.55_tile);

	eff.toggleBoinker();

	drive.goBackward(0.3_tile);

	drive.setToleranceParams(1_s);

	drive.faceToPoint({-0.1_tile,-10.5_tile}, true);

	drive.resetToleranceParams();

	drive.setToleranceParams(std::nullopt, 4_in);

	drive.goBackward(0.85_tile, {{0, 0.7}});

	drive.resetToleranceParams();

	pros::delay(300);

	eff.toggleClamp();

	drive.goForward(0.16_tile);

	eff.toggleIntakeState(SLOW);

	drive.setToleranceParams(0.75_s);

	is_blue ? drive.faceToPoint({20_tile, 0_tile}, true) : drive.faceToPoint({-20_tile, 0.1_tile}, true);

	drive.setToleranceParams(0.5_s);

	eff.toggleClamp();

	pros::delay(500);

	eff.toggleIntakeState(INACTIVE);

	drive.turnRight(175_deg);

	drive.setToleranceParams(0.5_s);

	drive.goBackward(1.7_tile);

	drive.resetToleranceParams();

	eff.toggleClamp();

	pros::delay(1000);

	drive.setToleranceParams(1_s);

	drive.turnRight(175_deg);

	drive.goForward(0.7_tile);

	drive.resetToleranceParams();

	eff.raiseArm();

	pros::delay(500);

	eff.stopArm();

	eff.toggleIntakeState(INACTIVE);

	*/;


	drive.move({
		DrivePoint({5.7283_tile, 1.7115_tile}, 0.3_tile, nullopt),
		DrivePoint({3.0221_tile, 0.9418_tile}, 0.3_tile, nullopt),
	});


	drive.move({
		DrivePoint({3.0221_tile, 0.9418_tile}, 0.3_tile, nullopt),
		DrivePoint({4.0814_tile, 0.9087_tile}, 0.3_tile, nullopt),
	});


	drive.move({
		DrivePoint({4.0814_tile, 0.9087_tile}, 0.3_tile, nullopt),
		DrivePoint({4.0152_tile, 2.0591_tile}, 0.3_tile, nullopt),
	});


	drive.move({
		DrivePoint({4.0152_tile, 2.0591_tile}, 0.3_tile, nullopt),
		DrivePoint({4.0731_tile, 3.0191_tile}, 0.3_tile, nullopt),
	});


}