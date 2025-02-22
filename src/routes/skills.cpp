#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"
#include <optional>

void Routes::skills () {

	OdomArc::setPos(0.1738_tile, 2.9979_tile, 90_deg);

	eff.setIntake(IntakeState::INTAKE);

    pros::delay(1000);

	auto lambda1 = [](){ eff.setIntake(IntakeState::INTAKE); };
	auto lambda2 = [](){ eff.setIntake(IntakeState::INACTIVE); };

	drive.move({
		DrivePoint({0.1738_tile, 2.9979_tile}, 0.3_tile, 1.5_tps, 20.42, lambda1),
		DrivePoint({0.451_tile, 2.9648_tile}, 0.3_tile, 1.5_tps, 20.42, nullopt),
		DrivePoint({0.6621_tile, 2.8903_tile}, 0.3_tile, 1.5_tps, 20.42, nullopt),
		DrivePoint({0.8441_tile, 2.7662_tile}, 0.3_tile, 1.5_tps, 20.42, nullopt),
		DrivePoint({2.2966_tile, 1.7152_tile}, 0.3_tile, 1.5_tps, 20.42, lambda2),
	});

	eff.setIntake(IntakeState::INACTIVE);


	drive.move({
		DrivePoint({2.2966_tile, 1.7152_tile}, 0.3_tile, 1.5_tps, 20.42, nullopt),
		DrivePoint({1.9738_tile, 1.9552_tile}, 0.3_tile, 1.5_tps, 20.42, nullopt),
	});

	drive.turnLeft(30_deg);


	drive.move({
		DrivePoint({1.9738_tile, 1.9552_tile}, 0.3_tile, 1.5_tps, 20.42, nullopt),
		DrivePoint({0.5752_tile, 1.9717_tile}, 0.3_tile, 1.5_tps, 20.42, nullopt),
	});

	eff.toggleClamp();

    /*

	eff.setIntake(IntakeState::INTAKE);


	drive.move({
		DrivePoint({0.5752_tile, 1.9717_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({2.371_tile, 0.5814_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({2.5697_tile, 0.4821_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({2.7683_tile, 0.4076_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({3_tile, 0.3828_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({3.1821_tile, 0.3745_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
	});


	drive.move({
		DrivePoint({3.1821_tile, 0.3745_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({2.851_tile, 0.7055_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({2.5034_tile, 0.8959_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({2.1972_tile, 0.929_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({1.7669_tile, 0.9207_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({0.0952_tile, 0.9207_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
	});

	drive.turnLeft(45_deg);


	drive.move({
		DrivePoint({0.0952_tile, 0.9207_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({0.9145_tile, 1.7648_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
	});

	drive.turnLeft(45_deg);


	drive.move({
		DrivePoint({0.9145_tile, 1.7648_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({0.8897_tile, 0.1924_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
	});

	drive.turnLeft(160_deg);


	drive.move({
		DrivePoint({0.8897_tile, 0.1924_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({0.0207_tile, 0.0352_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
	});

	drive.turnLeft(30_deg);

	eff.toggleClamp();

	auto lambda3 = [](){ eff.setIntake(IntakeState::INACTIVE); };

	drive.move({
		DrivePoint({0.0207_tile, 0.0352_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({1.6097_tile, 3.6352_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({1.8_tile, 3.7593_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({1.9159_tile, 3.9083_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({1.9572_tile, 4.289_tile}, 0.6_tile, 2.5_tps, 20.42, lambda3),
	});

	drive.turnLeft(90_deg);


	drive.move({
		DrivePoint({1.9572_tile, 4.289_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({0.6_tile, 4.0324_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
	});

	eff.toggleClamp();

	eff.setIntake(IntakeState::INTAKE);


	drive.move({
		DrivePoint({0.6_tile, 4.0324_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({2.189_tile, 5.2903_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({2.3545_tile, 5.4972_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({2.6193_tile, 5.5966_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({2.9834_tile, 5.6379_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({3.2979_tile, 5.6131_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
	});


	drive.move({
		DrivePoint({3.2979_tile, 5.6131_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({2.9669_tile, 5.3317_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({2.6772_tile, 5.1497_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({2.3048_tile, 5.0834_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({0.1283_tile, 5.1083_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
	});

	drive.turnRight(45_deg);


	drive.move({
		DrivePoint({0.1283_tile, 5.1083_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({0.8897_tile, 4.4959_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
	});

	drive.turnRight(45_deg);


	drive.move({
		DrivePoint({0.8897_tile, 4.4959_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({0.9145_tile, 5.8945_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
	});

	drive.turnRight(150_deg);


	drive.move({
		DrivePoint({0.9145_tile, 5.8945_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({0.0124_tile, 5.9772_tile}, 0.6_tile, 2.5_tps, 20.42, nullopt),
	});

	*/;


}