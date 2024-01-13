#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::elimDefensive () {
    OdomCustom::setPos(0_in, 0_in, -45_deg);
    
    drive.goForward(40_in);
    drive.turnRight(100_deg);
    eff.setIntake(true);
    pros::delay(1000);
    eff.setIntake(false, true);
    drive.turnLeft(100_deg);
    eff.setIntake();
    drive.goForward(5_in);
    drive.turnRight(150_deg);
    eff.setIntake(true);
    pros::delay(1000);
    eff.setIntake(false, true);
    drive.turnLeft(90_deg);
    eff.setIntake();
    drive.goForward(8_in);
    drive.turnRight(90_deg);
    eff.setIntake(true);
    pros::delay(500);
    eff.setIntake(false, true);
    eff.wingsToggle();
    drive.goForward(12_in);
}

