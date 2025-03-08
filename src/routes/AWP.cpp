#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

void Routes::AWPRed () {

	OdomArc::setPos(0.4014_tile, 3.4324_tile, -135_deg);

	drive.goForward(0.1_tile);

	// eff.raiseArm();
	eff.armRight.move_voltage(12000);

	pros::delay(800);

	// eff.lowerArm();
	eff.armRight.move_voltage(0);

	pros::delay(200);

	eff.stopArm();

	drive.doHeading = false;
	drive.goBackward(0.95_tile, 1.4_tps);

	drive.turnRight(45_deg); // won't be effected by doHeading
	
	drive.goBackward(1_tile, 1_tps);
	pros::delay(200);

	eff.toggleClamp();

	drive.turnRight(150_deg);
	drive.doHeading = true;

	/*;

	eff.setIntake(IntakeState::INTAKE);


	drive.move({
		DrivePoint({2.0897_tile, 4.111_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({2.371_tile, 4.3179_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({2.4621_tile, 4.7483_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({2.4786_tile, 5.0462_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({2.4621_tile, 5.2945_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({2.2883_tile, 5.7083_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({1.9407_tile, 5.7745_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({1.5931_tile, 5.7414_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({1.5103_tile, 5.3441_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({1.7669_tile, 4.1524_tile}, 0.6_tile, 2_tps, nullopt),
	});

	eff.toggleClamp();

	drive.turnRight(60_deg);


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