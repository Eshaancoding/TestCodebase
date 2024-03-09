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
    // prepare for under the bar
    drive.faceToPoint({0_in, -10_tile}, true);
    drive.goForward(2_tile, {{0, 1.5}});

    drive.setToleranceParams(nullopt, nullopt, 0.75_s);
    drive.turnLeft(45_deg);
    drive.resetToleranceParams();

    // go under the bar and hit the other side of the other side
    drive.goPath({
        Path({0_in, 0_in}, 1, 0.75),
        Path({-0.8_tile, 0.75_tile}, 1, 0.75),
        Path({-0.8_tile, 1_tile}, 1, 0.9),
        Path({-0.85_tile, 1.2_tile}, 0.3, 1.4),
        Path({-0.85_tile, 4_tile}, 1, 0.8, 0.3_tile),
        Path({0_tile, 5.15_tile}, 1, 0.8, 0.3_tile),
        Path({1.2_tile, 5.15_tile})
    }, 8_in, 5_in, true, 5_s);
    
    // go back
    drive.moveArcade(0.65, 0);
    pros::delay(300);
    drive.moveArcade(0, 0);

    // realign
    drive.setToleranceParams(nullopt, nullopt, 0.75_s);
    drive.faceToPoint({-10_tile, 0_tile}, true);
    drive.resetToleranceParams();

    // slam one more time
    drive.moveArcade(-1, 0);
    pros::delay(400);
    drive.moveArcade(0, 0);
    OdomCustom::setPos(0_in, 0_in, -90_deg);

    // ============== Go to center ==============
    // face to the back
    drive.setToleranceParams(nullopt, nullopt, 0.75_s);
    drive.faceToPoint({0_tile, 10_tile}, true);
    drive.resetToleranceParams();

    // go to center movement
    drive.goPath({
        Path({0_in, 0_in}, 1, 0.8, 0.3_tile),
        Path({4_in, -1.2_tile}, 1, 0.8, 0.3_tile, [](){
            eff.wingsPistonRight.set_value(1);
        }),
        Path({4_in, -1.35_tile}, 1, 0.8, 0.3_tile, [](){
            eff.wingsPistonLeft.set_value(1);
        }),
        Path({0.5_tile, -1.65_tile}, 1, 0.8, 0.3_tile),
        Path({0.85_tile, -1.73_tile}, 1, 0.8, 0.3_tile),
    }, 8_in, 6_in, true, 4.5_s);

    // turn to face the goal
    eff.wingsPistonRight.set_value(0);
    drive.setToleranceParams(nullopt, nullopt, 0.75_s);
    drive.faceToPoint({-30_tile, -40_tile}, true, {{0, 1.3}});
    drive.resetToleranceParams();
    eff.wingsPistonRight.set_value(1);
    
    // go slow at first
    drive.moveArcade(-0.55, 0);
    pros::delay(1200);
    
    // then go backward a little
    drive.moveArcade(0.8, 0);
    pros::delay(400);
    
    // slam!
    drive.moveArcade(-1, 0);
    pros::delay(700);
    
    // go back
    drive.moveArcade(1, 0);
    pros::delay(70);
    eff.wingsPistonRight.set_value(0);
    eff.wingsPistonLeft.set_value(0);
    pros::delay(600);
    drive.moveArcade(0, 0);

    // turn to the right
    drive.setToleranceParams(nullopt, nullopt, 0.75_s);
    drive.faceToPoint({-30_tile, 0_tile}, true);
    drive.resetToleranceParams();

    // ============== Right ==============
    // go to the right of the goal
    eff.wingsPistonLeft.set_value(1);
    eff.wingsPistonRight.set_value(0);
    drive.goBackward(1.5_tile);
    drive.setToleranceParams(nullopt, nullopt, 0.75_s);
    drive.faceToPoint({15_tile, -30_tile}, true);
    drive.resetToleranceParams();
    eff.wingsPistonRight.set_value(1);

    // go slow at first
    drive.moveArcade(-0.55, 0);
    pros::delay(1200);
    
    // go backward a little
    drive.moveArcade(0.8, 0);
    pros::delay(300);
    
    // slam!
    drive.moveArcade(-1, 0);
    pros::delay(700);
    
    // go back
    drive.moveArcade(0.5, 0);
    pros::delay(300);
    drive.moveArcade(0, 0);

    // retract wings
    eff.wingsPistonLeft.set_value(0);
    eff.wingsPistonRight.set_value(0);

    // ============== very Right ==============
    drive.faceToPoint({-30_tile, 0_tile}, true);

    drive.goPath({
        Path({0_in, 0_in}, 0.8, 1.3),
        Path({1_tile, 3_in}, 0.8, 1.3, 0.5_tile, [](){
            eff.wingsPistonLeft.set_value(1);
        }),
        Path({2_tile, 6_in})
    }, 5_in, 4_in, true, 3_s);

    drive.setToleranceParams(nullopt, nullopt, 0.75_s);
    drive.faceToPoint({25_tile, -35_tile}, true, {{0, 1}});
    drive.resetToleranceParams();

    drive.moveArcade(-1, -0.5);
    pros::delay(400);
    eff.wingsPistonLeft.set_value(0);
    pros::delay(350);
    
    // go backward a little
    drive.moveArcade(0.5, 0);
    pros::delay(200);
    
    // slam!
    drive.moveArcade(-1, -0.3);
    pros::delay(1200);

    // go back to not touch any triballs
    drive.moveArcade(1, 0.75);
    pros::delay(500);
    drive.moveArcade(0, 0);
}