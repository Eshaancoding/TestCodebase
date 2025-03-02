#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

//ringside rush
void Routes::test () {

	OdomArc::setPos(5.0069_tile, 2.9897_tile, 0_deg);


	drive.move({
		DrivePoint({5.0069_tile, 2.9897_tile}, 0.3_tile, 2.3_tps, 0, nullopt),
		DrivePoint({5.0069_tile, 3.9828_tile}, 0.3_tile, 1_tps, 0, nullopt),
		DrivePoint({5.0152_tile, 4.5041_tile}, 0.3_tile, 1_tps, 0, nullopt),
		DrivePoint({4.8579_tile, 4.8103_tile}, 0.3_tile, 1_tps, 0, nullopt),
		DrivePoint({4.6262_tile, 4.9841_tile}, 0.3_tile, 1_tps, 0, nullopt),
		DrivePoint({4.2952_tile, 5.0172_tile}, 0.3_tile, 1_tps, 0, nullopt),
		DrivePoint({3.9393_tile, 5.0586_tile}, 0.3_tile, 2.3_tps, 0, nullopt),
		DrivePoint({3.4759_tile, 5.0669_tile}, 0.3_tile, 2.3_tps, 0, nullopt),
		DrivePoint({2.971_tile, 5.0834_tile}, 0.3_tile, 2.3_tps, 0, nullopt),
	});


}