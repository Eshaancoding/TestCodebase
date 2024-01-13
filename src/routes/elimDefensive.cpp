#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::elimDefensive () {
    // note different corodinate system
    OdomCustom::setPos(0_in, 0_in, -33.69_deg);
    
    // go forward and outtake our match load
    drive.goForward(3.4_tile, {{0, 1.7}, {0.7, 0.6}});
    drive.turnRight(100_deg);
    eff.setIntake(true);
    pros::delay(1000);
    eff.setIntake(false, true);
    drive.turnLeft(100_deg);
    
    // intake the first triball and outtake
    eff.setIntake();
    drive.goForward(5_in);
    drive.turnRight(123_deg);
    eff.setIntake(true);
    pros::delay(1000);
    eff.setIntake(false, true);

    // make sure that you face the 90 degree angle
    OdomCustom::setPos(0_in, 0_in);
    drive.faceToPoint({0_tile, 20_tile}, true, {{0, 0.8}});

    // get the last two
    eff.setIntake();
    drive.goForward(8_in);
    drive.turnRight(90_deg);
    eff.setIntake(true);
    pros::delay(500);
    eff.setIntake(false, true);
    eff.wingsToggle();

    // slam
    drive.setToleranceParams(nullopt, nullopt, 1.7_s);
    drive.goForward(2.2_tile, {{0, 1.4}}, {{0.7, [](){
        eff.setIntake(true, false);
    }}});
    drive.resetToleranceParams();
}

