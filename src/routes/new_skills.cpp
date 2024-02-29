#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.h"
#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"
#include "odom/Math.h"
#include "AutonSelector.h"
#include "controller.h"

void Routes::new_skills () {
    macro(false);

    // ========= get the 4 middle triballs =======
    drive.goForward(2.2_tile);
    drive.faceToPoint({10_tile, -1_tile}, true);
    eff.wingsPistonLeft.set_value(1);
    drive.goBackward(2.75_tile, {{0, 1.5}});
    eff.wingsPistonLeft.set_value(0);

    // ========== Realign and go under bar ======
    drive.goBackward(6_in);
    
    OdomCustom::setPos(0_in, 0_in, -90_deg);
    drive.goPath({
        Path({0_in, 0_in}, 1, 0.8, 0.3_tile),
        Path({0_in, -0.5_tile}),
        Path({0_in, -1_tile}),
        Path({-1_tile, -1_tile}),
        Path({-1_tile, 2.2_tile}),
        Path({0_in, 3_tile}),
    }, 8_in, 3_in, true);

    // ============== Slam left side ==============
    drive.moveArcade(-1, 0);
    pros::delay(1000);
    drive.moveArcade(0, 0);
    drive.goPath({
        Path({0_in, 0_in}),
        Path({-0.5_tile, -0.25_tile}),
    }, 8_in, 3_in);
    drive.moveArcade(-1, 0);
    pros::delay(1000);
    drive.moveArcade(0,0);


    // ============== Go to center ==============
    drive.goPath({
        Path({0_tile, 0_tile}, 1, 0.8, 0.3_tile),
        Path({-0.4_tile, -0.4_tile}, 1, 0.8, 0.3_tile),
        Path({0_tile, -0.8_tile}),
        Path({2_tile, -1.75_tile})
    }, 8_in, 6_in);

    // ============== Slam center ==============
    drive.faceToPoint({0_tile, -10_tile}, true);
    eff.wingsToggle();
    drive.moveArcade(-1, 0);
    pros::delay(1200);
    drive.moveArcade(1,0);
    pros::delay(600);
    drive.moveArcade(0,0);
}