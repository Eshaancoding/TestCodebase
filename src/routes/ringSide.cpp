#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

//ringside rush
void Routes::ringSide () {

	OdomArc::setPos(5.7697_tile, 4.2605_tile, -1_deg);


	drive.move({
		DrivePoint({5.7697_tile, 4.2605_tile}, 0.3_tile, nullopt),
		DrivePoint({3.2372_tile, 5.0549_tile}, 0.3_tile, nullopt),
	});

	drive.turnRight(30_deg);


	drive.move({
		DrivePoint({3.2372_tile, 5.0549_tile}, 0.3_tile, nullopt),
		DrivePoint({4.0731_tile, 3.9791_tile}, 0.3_tile, nullopt),
	});

	eff.toggleIntake();


	drive.move({
		DrivePoint({4.0731_tile, 3.9791_tile}, 0.3_tile, nullopt),
		DrivePoint({4.0648_tile, 4.7239_tile}, 0.3_tile, nullopt),
		DrivePoint({4.0814_tile, 4.9887_tile}, 0.3_tile, nullopt),
		DrivePoint({4.1724_tile, 5.1046_tile}, 0.3_tile, nullopt),
		DrivePoint({4.4786_tile, 5.1874_tile}, 0.3_tile, nullopt),
		DrivePoint({4.9834_tile, 5.1791_tile}, 0.3_tile, nullopt),
		DrivePoint({5.1572_tile, 5.1543_tile}, 0.3_tile, nullopt),
	});


	drive.move({
		DrivePoint({5.1572_tile, 5.1543_tile}, 0.3_tile, nullopt),
		DrivePoint({5.8855_tile, 5.8494_tile}, 0.3_tile, nullopt),
	});


	drive.move({
		DrivePoint({5.8855_tile, 5.8494_tile}, 0.3_tile, nullopt),
		DrivePoint({5.8276_tile, 3.0025_tile}, 0.3_tile, nullopt),
	});


	drive.move({
		DrivePoint({5.8276_tile, 3.0025_tile}, 0.3_tile, nullopt),
		DrivePoint({4.0566_tile, 2.986_tile}, 0.3_tile, nullopt),
	});


	drive.move({
		DrivePoint({5.8359_tile, 3.0025_tile}, 0.3_tile, nullopt),
		DrivePoint({5.4717_tile, 5.0632_tile}, 0.3_tile, nullopt),
	});


}