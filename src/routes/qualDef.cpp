#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"

void Routes::qualDefensive() {
//     OdomArc::setPos(0_in, 0_in, -45_deg);
//     eff.setIntake(); 

//     eff.wingsPistonLeft.set_value(1);
//     drive.goBackward(13_in);
//     drive.turnLeft(30_deg);

//     drive.moveArcade(-1, 0);
//     pros::delay(300);
//     eff.wingsPistonLeft.set_value(0);
//     pros::delay(300);
//     drive.moveArcade(0.8, 0);
//     pros::delay(300);
//     drive.moveArcade(0, 0);

//     // slam the second triball
//     drive.turnLeft(160_deg, {{0, 0.8}});
//     drive.moveArcade(1, 0);
//     pros::delay(400);
//     drive.moveArcade(-0.6, 0);
//     pros::delay(300);
//     drive.moveArcade(0, 0);

//     // prepare for the in the middle movement
//     drive.faceToPoint({0_in, 10_tile}, true);
    
//     eff.setIntake();
    drive.goPath({
        Path({0_in, 0_in}),
        Path({0_in, 0.4_tile}),
        Path({1.85_tile, 2.2_tile}),
    }, 5_in, 15_in, false);

//     drive.faceToPoint({0_tile, -10_tile}, true);

//     drive.moveArcade(1, 0);
//     pros::delay(1000);
//     eff.setIntake(false, true);
//     drive.moveArcade(-1, 0);
//     pros::delay(800);
//     drive.moveArcade(0, 0);

//     drive.setToleranceParams(nullopt, nullopt, 0.75_s);
//     drive.faceToPoint({10_tile, 0_tile}, true);
//     drive.resetToleranceParams();
    
//     drive.moveArcade(-1, 0);
//     pros::delay(1000);
//     drive.moveArcade(0, 0);
    
//     drive.setToleranceParams(nullopt, nullopt, 1_s);
//     eff.wingsPistonLeft.set_value(1);
//     drive.turnLeft(20_deg);

}