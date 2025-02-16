#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

//ringside rush
void Routes::ringSide () {
    OdomArc::setPos(0_in, 0_in, 1_deg);
    eff.toggleBoinker();
    drive.move({
        DrivePoint({0_tile, 0_tile}, 0.3_tile, 0.2_tps, 20.32, nullopt),
        DrivePoint({0_tile, 3_tile}, 0.3_tile, 0.5_tps, 20.32, nullopt),
        DrivePoint({1_tile, 3_tile}, 0.3_tile, 0.3_tps, 20.32, nullopt),
    });
    drive.turnRight(72_deg);

    auto x = [](){ eff.setIntake(); };

    eff.toggleClamp();
    pros::delay(500);
    drive.resetToleranceParams();
    drive.turnLeft(90_deg);
    drive.move({
        DrivePoint({2_tile, 3_tile}, 0.3_tile, 0.2_tps, 20.32, nullopt),
        DrivePoint({4_tile, 3_tile}, 0.3_tile, 0.2_tps, 20.32, nullopt),
        DrivePoint({4_tile, 4_tile}, 0.3_tile, 0.6_tps, 30.32, x),
        DrivePoint({5_tile, 4_tile}, 0.3_tile, 0.2_tps, 20.32, nullopt),
    });
}