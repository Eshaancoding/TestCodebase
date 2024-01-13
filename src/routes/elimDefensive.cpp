#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::elimDefensive () {
    // note different corodinate system
    OdomCustom::setPos(0_in, 0_in, -41.01_deg);
    
    // go forward and outtake our match load
    eff.setIntake();
    drive.goForward(1.5_tile, {{0, 1.3}});
    drive.resetToleranceParams();

    drive.setToleranceParams(nullopt, nullopt, 0.5_s);
    drive.turnRight(80_deg);
    eff.setIntake(true, false);
    pros::delay(1000);
    eff.setIntake();
    drive.setToleranceParams(nullopt, nullopt, 1_s);
    drive.turnLeft(145_deg, {{0, 0.8}});

    // get triball
    drive.goForward(20_in);
    drive.goBackward(20_in);
    drive.turnRight(135_deg);
    eff.setIntake(true, false);
    pros::delay(1000);
    eff.setIntake(false, true);

    // then get the other two 
    // drive.turnLeft(90_deg);
    // eff.setIntake();
    // drive.goForward()
    
}

