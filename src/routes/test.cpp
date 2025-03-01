#include "parameters.h"
#include "routes.h"
#include "drive.h"
#include "odom/OdomArc.h"   

//ringside rush
void Routes::test () {

	OdomArc::setPos(0.9766_tile, 4.0159_tile, 0_deg);


	drive.move({
		DrivePoint({0.9766_tile, 4.0159_tile}, 0.3_tile, nullopt),
		DrivePoint({0.9766_tile, 4.5538_tile}, 0.3_tile, nullopt),
		DrivePoint({1.0841_tile, 4.769_tile}, 0.3_tile, nullopt),
		DrivePoint({1.291_tile, 4.9345_tile}, 0.3_tile, nullopt),
		DrivePoint({1.589_tile, 5.009_tile}, 0.3_tile, nullopt),
		DrivePoint({2.8552_tile, 5.0255_tile}, 0.3_tile, nullopt),
	});


}