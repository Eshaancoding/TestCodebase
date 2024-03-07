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
    drive.goForward(1.5_tile, {{0, 1.2}});
    drive.turnRight(180_deg);
    drive.goBackward(0.8_tile, {{0, 1.2}});
    drive.faceToPoint({10_tile, -1_tile}, true);

    eff.wingsPistonRight.set_value(1);
    eff.wingsPistonLeft.set_value(1);
    drive.moveArcade(-1, 0.06);
    pros::delay(1700);
    drive.moveArcade(0, 0);
    eff.wingsPistonLeft.set_value(0);
    eff.wingsPistonRight.set_value(0);

    // ========== Realign and go under bar ======
    drive.faceToPoint({0_in, -10_tile}, true);
    drive.goForward(2_tile, {{0, 1.5}});

    drive.setToleranceParams(nullopt, nullopt, 0.75_s);
    drive.turnLeft(45_deg);
    drive.resetToleranceParams();

    drive.goPath({
        Path({0_in, 0_in}, 1, 0.75),
        Path({-0.8_tile, 0.75_tile}, 1, 0.75),
        Path({-0.8_tile, 1_tile}, 1, 0.9),
        Path({-0.85_tile, 1.2_tile}, 0.3, 1.4),
        Path({-1_tile, 4_tile}, 1, 1.3, 0.3_tile),
        Path({0.9_tile, 5.1_tile})
    }, 8_in, 5_in, true, 5_s);
    
    drive.moveArcade(0.5, 0);
    pros::delay(200);
    drive.faceToPoint({-10_tile, 0_tile}, true);
    drive.moveArcade(-1, 0);
    pros::delay(400);
    drive.moveArcade(0.5, 0);
    pros::delay(200);
    drive.moveArcade(0, 0);

    // ============== Go to center ==============
        
    drive.faceToPoint({-0_tile, 10_tile}, true);
    drive.goPath({
        Path({0_in, 0_in}, 1, 0.8, 0.3_tile),
        Path({0_in, -1.2_tile}, 1, 0.8, 0.3_tile, [](){
            eff.wingsPistonRight.set_value(1);
        }),
        Path({0_in, -1.35_tile}, 1, 0.8, 0.3_tile, [](){
            eff.wingsPistonLeft.set_value(1);
        }),
        Path({0.5_tile, -1.65_tile}, 1, 0.8, 0.3_tile),
        Path({0.85_tile, -1.73_tile}, 1, 0.8, 0.3_tile),
        Path({1.2_tile, -1.8_tile}, 1, 0.8, 0.3_tile)
    }, 8_in, 6_in, true, 4.5_s);

    eff.wingsPistonRight.set_value(0);
    drive.faceToPoint({-15_tile, -40_tile}, true, {{0, 1.3}});
    eff.wingsPistonRight.set_value(1);
    drive.moveArcade(-0.55, 0);
    pros::delay(1200);
    drive.moveArcade(1, 0);
    pros::delay(400);
    drive.moveArcade(-1, 0);
    pros::delay(600);
    drive.moveArcade(0.5, 0);
    pros::delay(300);
    drive.moveArcade(0, 0);

    // ============== Right ==============
    eff.wingsPistonLeft.set_value(0);
    eff.wingsPistonRight.set_value(0);
    drive.goPath({
        Path({0_in, 0_in}),
        Path({0_in, -0.8_tile}),
        Path({1.3_tile, -0.8_tile}),
    }, 8_in, 6_in, false, 4_s);

    drive.faceToPoint({30_tile, -50_tile}, true, {{0, 1.3}});
    
    eff.wingsPistonLeft.set_value(1);
    eff.wingsPistonRight.set_value(1);
    drive.moveArcade(-0.55, 0);
    pros::delay(1200);
    drive.moveArcade(1, 0);
    pros::delay(400);
    drive.moveArcade(-1, 0);
    pros::delay(600);
    drive.moveArcade(0.5, 0);
    pros::delay(300);
    drive.moveArcade(0, 0);


    eff.wingsPistonLeft.set_value(0);
    eff.wingsPistonRight.set_value(0);

    // ============== very Right ==============
    OdomCustom::setPos(0_in, 0_in, -180_deg);
    
    drive.goForward(1_tile);

    drive.setToleranceParams(nullopt, nullopt, 0.5_s);
    drive.faceToPoint({-30_tile, -10_tile}, true);
    drive.resetToleranceParams();
    
    eff.wingsPistonLeft.set_value(1);
    drive.goPath({
        Path({0_in, 0_in}, 0.4, 1.2),
        Path({1.65_tile, 1_tile}),
        Path({1.65_tile, 1.5_tile}),
        Path({1.5_tile, 1.75_tile}),
    }, 8_in, 12_in, true, 5_s);

    drive.faceToPoint({40_tile, -30_tile}, true, {{0, 1.3}});
    eff.wingsPistonLeft.set_value(0);
    drive.moveArcade(0.5, 0);
    pros::delay(200);
    drive.moveArcade(-1, -0.3);
    pros::delay(1200);
    drive.moveArcade(1, 0.5);
    pros::delay(500);
    drive.moveArcade(0, 0);
}