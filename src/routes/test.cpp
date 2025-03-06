#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

//ringside rush
void Routes::test () {

	OdomArc::setPos(0_tile, 0_tile, 0_deg);


	drive.move({
		DrivePoint({0_tile, 0_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({-0.5_tile, 1.5_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({-1.0_tile, 2_tile}, 0.6_tile, 1_tps, nullopt),
	});


}