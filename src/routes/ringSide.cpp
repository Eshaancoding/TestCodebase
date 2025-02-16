#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

//ringside rush
void Routes::ringSide () {
	OdomArc::setPos(0.7034_tile, 4.9593_tile, 90_deg);


	drive.move({
		DrivePoint({0.7034_tile, 4.9593_tile}, 0.3_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({3.8814_tile, 4.8848_tile}, 0.3_tile, 3.5_tps, 20.42, nullopt),
		DrivePoint({4.8828_tile, 2.7497_tile}, 0.3_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({4.7421_tile, 1.1938_tile}, 0.3_tile, 2.5_tps, 20.42, nullopt),
	});


}