#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

//ringside rush
void Routes::ringSide () {
	auto lambda1 = [](){ eff.setIntake(); };
	auto lambda2 = [](){ eff.setLog(); };

	drive.move({
		DrivePoint({1.848_tile, 4.9657_tile}, 0.3_tile, 2_tps, 20.42, nullopt),
		DrivePoint({5.0673_tile, 4.6926_tile}, 0.3_tile, 2.6_tps, 20.42, lambda1),
		DrivePoint({4.7859_tile, 2.483_tile}, 0.3_tile, 2.3_tps, 20.42, nullopt),
		DrivePoint({2.7583_tile, 0.9768_tile}, 0.3_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({0.9707_tile, 1.9368_tile}, 0.3_tile, 2.5_tps, 20.42, lambda2),
		DrivePoint({4.2397_tile, 1.192_tile}, 0.3_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({4.8788_tile, 1.523_tile}, 0.3_tile, 2.5_tps, 20.42, nullopt),
	});

	pros::delay(500);

	drive.turnLeft(75_deg);

	pros::delay(500);


}