#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

//ringside rush
void Routes::test () {

	OdomArc::setPos(0.9652_tile, 2.9713_tile, 180_deg);


	drive.move({
		DrivePoint({0.9652_tile, 2.9713_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({0.9569_tile, 2.7395_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({0.9486_tile, 2.5326_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({1.0397_tile, 2.3092_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({1.2549_tile, 2.0278_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({2.4052_tile, 1.6057_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({2.67_tile, 1.2499_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({2.7528_tile, 0.894_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({2.728_tile, 0.4968_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({2.488_tile, 0.3064_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({2.1652_tile, 0.2071_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({1.8424_tile, 0.3147_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({1.6438_tile, 0.5713_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({1.528_tile, 0.9933_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({1.5942_tile, 1.4402_tile}, 0.6_tile, 1_tps, nullopt),
		DrivePoint({1.8424_tile, 1.8623_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({4.3997_tile, 4.5602_tile}, 0.6_tile, 2_tps, nullopt),
	});


}