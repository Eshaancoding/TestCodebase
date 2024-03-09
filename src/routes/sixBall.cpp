#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::sixBall () {
    // =========== match triball go away =========== 
    OdomCustom::setPos(0_in, 0_in, 0_deg);
    eff.setIntake();
    drive.goPath({
        Path({0_in, 0_in}, 1, 1.2),
        Path({0_tile, 0.5_tile}, 1, 1.2),
        Path({-1.5_tile, 2.4_tile})
    }, 4_in, 3_in, false, 3_s);

    pros::delay(300);

    // =========== slam at mid =========== 
    drive.faceToPoint({10_tile, 0_in}, true);

    eff.setIntake(false, true);
    drive.moveArcade(1, 0);
    pros::delay(800);
    drive.moveArcade(0, 0);
    OdomCustom::setPos(0_in, 0_in, 0_deg);

    // =========== get the triball on right =========== 
    drive.goPath({
        Path({0_in, 0_in}),
        Path({0.45_tile, -1_tile})
    }, 4_in, 3_in, true);

    drive.setToleranceParams(nullopt, nullopt, 0.75_s);
    drive.turnRight(180_deg);
    drive.resetToleranceParams();

    eff.setIntake(); 
    drive.goForward(15_in);

    // // =========== curve movement to the right side =========== 
    // // ================ and get triball =======================
    drive.setToleranceParams(nullopt, nullopt, 0.6_s);
    drive.turnRight(50_deg, {{0, 1.4}});
    drive.resetToleranceParams();

    drive.goPath({
        Path({0_in, 0_in}, 1.2, 1, 0.3_tile), 
        Path({0.65_tile, 0.8_tile}, 1.2, 1, 0.3_tile),
        Path({1_tile, 0.9_tile}, 1.2, 1, 0.3_tile),
        Path({1.25_tile, 0.8_tile}, 1.2, 1, 0.3_tile),
        Path({1.28_tile, 0_tile}, 1.2, 1, 0.3_tile, [](){
            eff.setIntake(true, false); 
        }),
        Path({1.28_tile, -0.3_tile}),
    }, 8_in, 7_in, true);

    eff.setIntake();
    
    drive.faceToPoint({0_in, -10_tile}, true);

    drive.goForward(6_in);
    
    drive.goPath({
        Path({0_in, 0_in}, 1.2, 1.2),
        Path({0_tile, 1.15_tile}, 1.2, 1.2, 0.5_tile, [](){
            eff.wingsPistonLeft.set_value(1);
        }),
        Path({-0.6_tile, 2.15_tile}, 1.2, 1.2, 0.5_tile),
        Path({-1_tile, 2.15_tile}, 1.2, 1.2, 0.5_tile, [](){
            eff.wingsPistonLeft.set_value(0);
        }),
        Path({-1.2_tile, 2.15_tile})
    }, 8_in, 5_in, true, 2.3_s);
    eff.setIntake(false, true);
    
    drive.moveArcade(0.5, 0);
    pros::delay(200);
    
    drive.setToleranceParams(nullopt, nullopt, 1.6_s);
    drive.turnLeft(160_deg, {{0, 1.2}});
    drive.resetToleranceParams();

    drive.moveArcade(1, 0);
    pros::delay(400);
    drive.moveArcade(-0.6, 0);
    pros::delay(300);
    drive.moveArcade(0, 0);
}
