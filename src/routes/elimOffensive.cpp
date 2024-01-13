#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::elimOffensive() {

    OdomCustom::setPos(0_in, 0_in, -90_deg);

    drive.goForward(2.5_tile, {{0, 1.4}, {0.7, 0.6}}); // slow down a lot at the end
    drive.turnLeft(90_deg);
    
    eff.setIntake(true, false);
    eff.wingsToggle();

    // slam
    drive.setToleranceParams(nullopt, nullopt, 1.7_s);
    drive.goBackward(2.2_tile, {{0, 1.4}});
    drive.resetToleranceParams();

    eff.setIntake(false, true);
    eff.wingsToggle();

    // move backwards a bit just in case
    pros::delay(2000);
    drive.goForward(1_tile);
    
    // try to intake the last one
    drive.turnRight(135_deg);
    eff.setIntake();
    drive.goForward(1.41_in, {{0, 0.7}});
}