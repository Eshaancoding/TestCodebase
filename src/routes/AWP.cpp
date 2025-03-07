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

	eff.stopArm();


	drive.move({
		DrivePoint({0.4014_tile, 3.4324_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({2.0814_tile, 4.111_tile}, 0.6_tile, 2_tps, nullopt),
	});

	eff.lowerArm();
	pros::delay(1000);

	eff.toggleClamp();

	drive.turnLeft(170_deg);

	/*;

	eff.setIntake(IntakeState::INTAKE);

	eff.toggleClamp();


	drive.move({
		DrivePoint({2.0317_tile, 4.0697_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({2.52_tile, 4.3924_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({2.7103_tile, 4.6076_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({2.8428_tile, 4.9552_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({2.8179_tile, 5.3938_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({2.6359_tile, 5.7331_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({2.28_tile, 5.6917_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({2.04_tile, 5.4683_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({1.9821_tile, 5.0876_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({1.9821_tile, 4.5993_tile}, 0.6_tile, 2_tps, nullopt),
	});

	drive.turnRight(30_deg);


	drive.move({
		DrivePoint({1.9821_tile, 4.5993_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({0.9062_tile, 2.911_tile}, 0.6_tile, 2_tps, nullopt),
	});

	eff.setIntake(IntakeState::INACTIVE);

	drive.turnRight(90_deg);


	drive.move({
		DrivePoint({0.9062_tile, 2.911_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({2.0317_tile, 1.951_tile}, 0.6_tile, 2_tps, nullopt),
	});

	eff.toggleClamp();

	*/;


}