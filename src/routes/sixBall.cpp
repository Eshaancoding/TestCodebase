#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::sixBall () {
    OdomCustom::setPos(0_in, 0_in, -68_deg);
    
    // =========== match triball go away =========== 
    eff.setIntake(true, false);
    pros::delay(400);
    eff.setIntake(false, true);

    // =========== go to mid =========== 
    eff.setIntake();
    drive.goPath({
        Path({0_in, 0_in}, 1.25, 1.25),
        Path({-2.3_tile, -1.9_tile})
    }, 8_in, 4_in, false, 4_s);

    // =========== slam at mid =========== 
    drive.setToleranceParams(nullopt, nullopt, 1.75_s);
    drive.turnRight(145_deg, {{0, 0.8}});
    drive.resetToleranceParams();

    eff.setIntake(false, true);
    drive.moveArcade(1, 0);
    pros::delay(1000);
    drive.moveArcade(0, 0);
    OdomCustom::setPos(0_in, 0_in, 0_deg);

    // =========== get the triball on right =========== 
    // drive.moveArcade(-1, 0);
    // pros::delay(100);
    drive.goPath({
        Path({0_in, 0_in}),
        Path({0.45_tile, -1_tile})
    }, 4_in, 3_in, true);

    drive.setToleranceParams(nullopt, nullopt, 0.75_s);
    drive.turnRight(180_deg);
    drive.resetToleranceParams();

    eff.setIntake(); 
    drive.goForward(20_in);

    // // =========== curve movement to the right side =========== 
    // // ================ and get triball =======================
    drive.setToleranceParams(nullopt, nullopt, 0.5_s);
    drive.turnRight(60_deg, {{0, 1.5}});
    drive.resetToleranceParams();

    drive.goPath({
        Path({0_in, 0_in}, 1.5, 1, 0.3_tile), 
        Path({0.65_tile, 0.9_tile}, 1.2, 1, 0.3_tile),
        Path({1_tile, 0.9_tile}, 1.5, 1, 0.3_tile),
        Path({1.25_tile, 0.9_tile}, 1.3, 1, 0.3_tile, [](){
            eff.setIntake(true, false);
        }),
        Path({1.4_tile, 0_tile}, 1, 1, 0.3_tile),
    }, 8_in, 5_in, true);

    eff.setIntake();
    
    drive.faceToPoint({0_in, -10_tile}, true);
    drive.goForward(1_tile);
    drive.goBackward(1.6_tile);
    drive.turnLeft(45_deg, {{0, 0.8}});

    eff.wingsPistonLeft.set_value(1);
    drive.goBackward(13_in);
    drive.turnLeft(30_deg);

    drive.moveArcade(-1, 0);
    pros::delay(300);
    eff.wingsPistonLeft.set_value(0);
    pros::delay(300);
    drive.moveArcade(0.8, 0);
    pros::delay(300);
    drive.moveArcade(0, 0);

    // slam the second triball
    drive.turnLeft(160_deg, {{0, 0.8}});
    drive.moveArcade(1, 0);
    pros::delay(400);
    drive.moveArcade(-0.6, 0);
    pros::delay(300);
    drive.moveArcade(0, 0);
}
