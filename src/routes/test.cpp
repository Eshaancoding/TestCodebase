#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

//ringside rush
void Routes::test () {

	OdomArc::setPos(0.9321_tile, 3.0044_tile, 180_deg);


	drive.move({
		DrivePoint({0.9321_tile, 3.0044_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({0.9321_tile, 2.1106_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({0.9486_tile, 1.8292_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({1.0397_tile, 1.5561_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({1.3542_tile, 1.4899_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({1.619_tile, 1.6885_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({4.35_tile, 4.254_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({4.6397_tile, 4.2954_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({4.9045_tile, 4.2209_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({5.0204_tile, 4.0057_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({5.0452_tile, 3.7575_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({5.0369_tile, 2.9795_tile}, 0.6_tile, 2_tps, nullopt),
	});


}