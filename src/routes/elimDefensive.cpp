#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::elimDefensive () {
    // note different corodinate system 
    eff.slapper.move_voltage(12000);
    eff.smallerSlapper.move_velocity(-100);
    pros::delay(1000);
    eff.slapper.move_voltage(0);
    eff.smallerSlapper.move_velocity(0);

    OdomCustom::setPos(0_in, 0_in, -41.01_deg);
    
    // go forward and outtake our match load
    eff.setIntake();
    drive.goForward(1.7_tile, {{0, 1.3}});
    drive.resetToleranceParams();

    drive.setToleranceParams(nullopt, nullopt, 0.5_s);
    drive.turnRight(80_deg);
    eff.setIntake(true, false);
    pros::delay(650);
    eff.setIntake();
    drive.setToleranceParams(nullopt, nullopt, 1_s);
    drive.turnLeft(145_deg, {{0, 0.9}});

    // get triball
    drive.goForward(20_in);
    drive.goBackward(20_in);
    drive.turnRight(135_deg, {{0, 0.9}});
    eff.setIntake(true, false);
    pros::delay(650);
    eff.setIntake();

    // then get the last triball
    drive.setToleranceParams(nullopt, nullopt, 1.5_s);
    drive.turnLeft(85_deg, {{0, 0.9}});
    drive.goForward(1.6_tile);
    pros::delay(500);
    
    // make sure to do this
    drive.faceToPoint({10_tile, 0_tile}, true);
    
    // slam
    eff.wingsToggle();
    eff.setIntake(true, false);
    drive.moveArcade(1, 0);
    pros::delay(1000);
    drive.moveArcade(0, 0);
    eff.wingsToggle();
    eff.setIntake(false, true);
}

