#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

//ringside rush
void Routes::test () {

	OdomArc::setPos(0.568_tile, 3.923_tile, 90_deg);


	drive.move({
		DrivePoint({0.568_tile, 3.923_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({1.95_tile, 4.5768_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({4.3583_tile, 4.1299_tile}, 0.6_tile, 2_tps, nullopt),
		DrivePoint({4.7555_tile, 2.9216_tile}, 0.6_tile, 2_tps, nullopt),
	});


}