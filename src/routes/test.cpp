#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

//ringside rush
void Routes::test () {

	OdomArc::setPos(0.9678_tile, 4.1317_tile, 0_deg);

	drive.move({
		DrivePoint({0.9683_tile, 4.1317_tile}, 7_in, 0.5_tps, 20.42, nullopt),
		DrivePoint({0.9766_tile, 4.5538_tile}, 7_in, 0.5_tps, 20.42, nullopt),
		DrivePoint({1.0841_tile, 4.769_tile}, 7_in, 0.5_tps, 20.42, nullopt),
		DrivePoint({1.291_tile, 4.9345_tile}, 7_in, 0.5_tps, 20.42, nullopt),
		DrivePoint({1.589_tile, 5.009_tile}, 7_in, 0.5_tps, 20.42, nullopt),
		DrivePoint({2.8552_tile, 5.0255_tile}, 7_in, 2.5_tps, 20.42, nullopt),
	});


}