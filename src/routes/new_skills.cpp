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
    macro(true);

    // ========= get the 4 middle triballs =======
    eff.setIntake(true, false); // reverse intake
    drive.goForward(2.3_tile, {{0, 1.5}});
    drive.faceToPoint({10_tile, -1_tile}, true);
    eff.setIntake(false, true); // reverse intake

    eff.wingsPistonRight.set_value(1);
    eff.wingsPistonLeft.set_value(1);
    drive.moveArcade(-1, 0);
    pros::delay(2300);
    drive.moveArcade(0, 0);
    eff.wingsPistonLeft.set_value(0);
    eff.wingsPistonRight.set_value(0);

    // ========== Realign and go under bar ======
    // drive.goForward(4_in);
    drive.goForward(1_tile);
    
    drive.goPath({
        Path({0_in, 0_in}, 1, 0.7, 0.3_tile),
        Path({-1_tile, -1_tile}, 1, 0.7, 0.3_tile),
        Path({-1.35_tile, -1_tile}, 1, 0.7, 0.3_tile),
        Path({-1.5_tile, -0.5_tile}, 1, 0.7, 0.3_tile),
        Path({-1.5_tile, 0.5_tile}, 0.4, 1.4),
        Path({-1.5_tile, 1.85_tile}, 0.4, 1.4),
        Path({0_tile, 2.6_tile}),
    }, 14_in, 3_in, true, 6.5_s);

    // ============== Slam left side ==============
    
    // eff.wingsPistonLeft.set_value(1);
    // drive.moveArcade(-1, 0);
    // pros::delay(300);
    // eff.wingsPistonLeft.set_value(0);
    // pros::delay(700);
    // drive.moveArcade(0, 0);
    // drive.goPath({
    //     Path({0_in, 0_in}),
    //     Path({-0.5_tile, -0.25_tile}),
    // }, 8_in, 3_in);
    // drive.moveArcade(-1, 0);
    // pros::delay(1000);
    // drive.moveArcade(0,0);

    // ============== Go to center ==============
    drive.faceToPoint({0_in, 30_tile}, true);
    drive.goPath({
        Path({0_in, 0_in}, 1, 0.8, 0.3_tile),
        Path({0_tile, -1_tile}, 1, 0.8, 0.3_tile, [](){
            eff.wingsPistonLeft.set_value(1);
            eff.wingsPistonRight.set_value(1);
        }),
        Path({0.5_tile, -1.5_tile}, 1, 0.8, 0.3_tile),
        Path({1_tile, -1.5_tile}, 1, 0.8, 0.3_tile),
        Path({1.25_tile, -0.75_tile}, 1, 0.8, 0.3_tile),
        Path({1.5_tile, 0_tile}, 1, 0.8, 0.3_tile),
    }, 8_in, 6_in, true, 5_s);

    // ============== Slam center ==============
    // drive.faceToPoint({0_tile, -10_tile}, true, {{0, 0.7}});
    drive.moveArcade(1, 0);
    pros::delay(600);
    drive.moveArcade(-1,0);
    pros::delay(1200);
    drive.moveArcade(0,0);
}