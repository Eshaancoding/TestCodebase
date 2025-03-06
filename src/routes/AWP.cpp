#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

void Routes::AWPRed () {

	OdomArc::setPos(0.4014_tile, 3.4324_tile, -115_deg);

	eff.raiseArm();

	pros::delay(1000);

	eff.lowerArm();

	pros::delay(1500);

	eff.stopArm();


	drive.move({
		DrivePoint({0.4014_tile, 3.4324_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({2.3628_tile, 4.1855_tile}, 0.6_tile, 2_tps, nullopt),
	});

	eff.toggleClamp();

	drive.turnLeft(180_deg);

	/*;

	eff.setIntake(IntakeState::INTAKE);


	drive.move({
		DrivePoint({2.0317_tile, 4.0697_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({2.52_tile, 4.3924_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({2.7103_tile, 4.6076_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({2.8428_tile, 4.9552_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({2.8097_tile, 5.5428_tile}, 0.6_tile, 1_tps, nullopt),
	});

	*/;


}