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
    pros::delay(1700);
    drive.moveArcade(0, 0);
    eff.wingsPistonLeft.set_value(0);
    eff.wingsPistonRight.set_value(0);

    // ========== Realign and go under bar ======
    drive.goForward(4_in);
    drive.goForward(1_tile);
    
    drive.goPath({
        Path({0_in, 0_in}, 1, 0.7, 0.3_tile),
        Path({-1_tile, -1_tile}, 1, 0.7, 0.3_tile),
        Path({-1.35_tile, -1_tile}, 1, 0.7, 0.3_tile),
        Path({-1.5_tile, -0.5_tile}, 1, 0.7, 0.3_tile),
        Path({-1.5_tile, 0.5_tile}, 0.4, 1.4, 0.3_tile),
        Path({-1.5_tile, 1.4_tile}, 0.4, 1.4, 0.3_tile, [](){
            eff.wingsPistonLeft.set_value(1);
        }),
        Path({-1.5_tile, 2_tile}, 0.4, 1.4),
        Path({0_tile, 2.6_tile}),
    }, 14_in, 3_in, true, 6.5_s);
    
    drive.moveArcade(0.5, 0);
    pros::delay(200);
    drive.moveArcade(0, 0);
    eff.wingsPistonLeft.set_value(0);

    // ============== Go to center ==============
        
    OdomCustom::setPos(0_in, 0_in, -90_deg); // ============ DELETE THIS LATER =====

    drive.faceToPoint({0_in, 30_tile}, true);
    drive.goPath({
        Path({0_in, 0_in}, 1, 0.8, 0.3_tile),
        Path({0_tile, -1.25_tile}, 1, 0.8, 0.3_tile, [](){
            eff.wingsPistonLeft.set_value(1);
            eff.wingsPistonRight.set_value(1);
        }),
        Path({0_in, -1.35_tile}, 1, 0.8, 0.3_tile),
        Path({0.5_tile, -1.65_tile}, 1, 0.8, 0.3_tile),
        Path({1.4_tile, -0.5_tile}, 1, 0.8, 0.3_tile)
    }, 8_in, 1_tile, true, 4.5_s);

    drive.moveArcade(-1, 0);
    pros::delay(1200);
    drive.moveArcade(0.5, 0);
    pros::delay(200);
    drive.moveArcade(0, 0);

    // ============== Right ==============
    eff.wingsPistonLeft.set_value(0);
    eff.wingsPistonRight.set_value(0);
    drive.goPath({
        Path({0_in, 0_in}),
        Path({0_in, -0.8_tile}),
        Path({1.5_tile, -0.8_tile}),
    }, 8_in, 6_in, false, 4_s);

    drive.faceToPoint({30_tile, -40_tile}, true);
    
    eff.wingsPistonLeft.set_value(1);
    eff.wingsPistonRight.set_value(1);
    drive.moveArcade(-1, 0);
    pros::delay(1200);
    drive.moveArcade(0, 0);
    eff.wingsPistonLeft.set_value(0);
    eff.wingsPistonRight.set_value(0);

    // ============== very Right ==============
    OdomCustom::setPos(0_in, 0_in, 180_deg); // ============ DELETE THIS LATER =====
    drive.goPath({
        Path({0_in, 0_in}),
        Path({0_in, -0.25_tile}),
        Path({2_tile, 0.5_tile}),
    }, 8_in, 6_in);
    drive.faceToPoint({10_tile * 1, 10_tile * -1.25}, true);
    drive.moveArcade(-1, 0);
    pros::delay(1200);
    drive.moveArcade(1, 0);
    pros::delay(600);
    drive.moveArcade(0, 0);
}