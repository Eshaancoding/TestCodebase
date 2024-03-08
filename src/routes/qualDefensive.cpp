#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::qualDefensive () {
    drive.moveArcade(1, 0.47);
    pros::delay(600);
    eff.setIntake(true, false); // reverse intake
    pros::delay(400);
    eff.setIntake(false, true); // reverse intake
    drive.moveArcade(0.5, 0);
    pros::delay(300);
    drive.moveArcade(0, 0);

    OdomCustom::setPos(0_in, 0_in, 0_deg);
    drive.goPath({
        Path({0_in, 0_in}, 1, 0.8, 0.3_tile),
        Path({0_in, -0.5_tile}, 1.1, 0.8, 0.3_tile),
        Path({4_in, -0.8_tile}, 1.1, 0.8, 0.3_tile, [](){
            eff.wingsPistonLeft.set_value(1);
        }),
        Path({12_in, -1.3_tile}, 1, 1, 0.5_tile, [](){
            eff.wingsPistonLeft.set_value(0);
        }),
        Path({12_in, 1.25_tile}),
        // Path({1.2_tile, 2_tile})
    }, 3_in, 5_in, true);


    drive.setToleranceParams(nullopt, nullopt, 0.75_s);
    drive.faceToPoint({-10_tile, 0_tile}, true);
    drive.resetToleranceParams();

    eff.wingsPistonLeft.set_value(1);
    eff.wingsPistonRight.set_value(1);
    
    drive.moveArcade(-1, 0);
    pros::delay(1000);
    drive.moveArcade(0, 0);
    eff.wingsPistonLeft.set_value(0);
    
    drive.setToleranceParams(nullopt, nullopt, 0.75_s);
    drive.faceToPoint({0_tile, 10_tile}, true);
    drive.resetToleranceParams();
    
    drive.goBackward(1.65_tile, {{0, 1.5}});
    
    drive.setToleranceParams(nullopt, nullopt, 1.5_s);
    drive.turnRight(20_deg);
}