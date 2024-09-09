#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"   

void Routes::skills () {
    OdomCustom::setPos(0_in, 0_in, 90_deg);
    eff.intakeToggle();
    pros::delay(1000);
    eff.intakeToggle();

    drive.goPath({ // REALLY REALLY REALLY TUNABLE!!!
        Path({0_in, 0_in}),
        Path({1_tile, 0_in}),
        Path({2_tile, -1_tile})
    }); // don't have to be too accurate!

    drive.faceToPoint({3_tile, 0_in}, true);
    drive.goBackward(1_tile);
    eff.toggleClamp();
    drive.goPath({
        Path({0_in, 0_in}),
        Path({1_tile, -0.5_tile}),
        Path({2_tile, -1.5_tile})
    });

    drive.faceToPoint({-1_tile, 0.5_tile}, true);

    drive.goPath({
        Path({-0.5_tile, 0.5_tile}),
        Path({-1_tile, 0.5_tile}),
        Path({-2.5_tile, 0.5_tile})
    });

    drive.faceToPoint({0.5_tile, -0.5_tile}, true);
    drive.goForward(0.707_tile);
    drive.faceToPoint({1_tile, 0.5_tile}, true);
    drive.goBackward(1.118_tile);
    eff.toggleClamp();

    //second part skills auton
    drive.goForward(4.472_tile);
    drive.faceToPoint({2_tile, 0_tile}, true);
    eff.intakeToggle();
    drive.goBackward(1_tile);
    eff.toggleClamp();
    eff.intakeToggle();
    drive.goPath({
        Path({1_tile, 0.3_tile}),
        Path({1.75_tile, 0.75_tile}),
        Path({2_tile, 1.5_tile})
    });

    drive.goPath({
        Path({-1_tile, -0.5_tile}),
        Path({-2.5_tile, -0.5_tile})
    });

    drive.faceToPoint({0.5_tile, 0.5_tile}, true);
    drive.goForward(0.707_tile);
    drive.faceToPoint({1_tile, -0.5_tile}, true);
    drive.goBackward(1.118_tile);
    eff.toggleClamp();

}