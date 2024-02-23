#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::sixBall () {
    OdomCustom::setPos(0_in, 0_in, -90_deg);
    
    eff.setIntake();
    drive.goPath({
        Path({0_tile, 0_tile}, 1, 1.4),
        Path({-0.7_tile, 0_tile}, 1, 1.4),
        Path({-2.4_tile, -1.6_tile}, 1, 1.4)
    }, 8_in, 6_in);

    drive.faceToPoint({0_in, 10_tile}, true);
    drive.moveArcade(1, 0);
    pros::delay(800);
    drive.moveArcade(0, 0);
    eff.setIntake(false, true);

    // drive.goBackward(1_tile);
    // drive.faceToPoint({10_tile, 10_tile})
}
