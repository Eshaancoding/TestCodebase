#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::qualOffensive() {
    OdomCustom::setPos(0_in, 0_in, -45_deg);
    eff.setIntake(); 

    eff.wingsPistonLeft.set_value(1);
    drive.goBackward(13_in);
    drive.turnLeft(30_deg);

     

    drive.moveArcade(-1, 0);

    pros::delay(300);
    eff.wingsPistonLeft.set_value(0);
    pros::delay(300);

    drive.turnRight(90_deg);
    
    eff.setIntake();
    OdomCustom::setPos(0_in, 0_in, 0_deg);
    drive.goPath({
        Path({0_in, 0_in}),
        Path({0_in, 0.4_tile}),
        Path({1.85_tile, 2.2_tile}),
    }, 3_in, 5_in, false);

    drive.faceToPoint({0_tile, -10_tile}, true);

    drive.moveArcade(1, 0);
    pros::delay(1000);
    drive.moveArcade(-1, 0);
    pros::delay(800);
    drive.moveArcade(0, 0);

    drive.setToleranceParams(nullopt, nullopt, 0.75_s);
    drive.faceToPoint({10_tile, 0_tile}, true);
    drive.resetToleranceParams();
    
    drive.moveArcade(-1, 0);
    pros::delay(1000);
    drive.moveArcade(0, 0);
    
    drive.setToleranceParams(nullopt, nullopt, 1.5_s);
    drive.turnLeft(20_deg);

}