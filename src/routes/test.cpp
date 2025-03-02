#include "parameters.h"
#include "routes.h"
#include "drive.h"
#include "odom/OdomArc.h"   
#include <optional>

//ringside rush
void Routes::test () {

	OdomArc::setPos(0.9683_tile, 3.9662_tile, 0_deg);


	drive.move({
		DrivePoint({0.9683_tile, 3.9662_tile}, 0.4_tile, nullopt),
		DrivePoint({0.9766_tile, 4.5869_tile}, 0.4_tile, nullopt),
		DrivePoint({1.1338_tile, 4.8848_tile}, 0.4_tile, nullopt),
		DrivePoint({1.4317_tile, 5.0421_tile}, 0.4_tile, nullopt),
		DrivePoint({1.9448_tile, 5.0338_tile}, 0.4_tile, nullopt),
		DrivePoint({2.8966_tile, 5.0421_tile}, 0.4_tile, nullopt),
	});


}