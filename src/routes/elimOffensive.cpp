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
    drive.turnLeft(90_deg, {{0, 0.7}});
    
    eff.setIntake(true, false);

    // slam
    drive.moveArcade(-1, 0);
    pros::delay(1000);
    drive.moveArcade(0, 0);

    eff.setIntake(false, true);

    // move backwards a bit just in case
    pros::delay(2000);
    drive.goForward(1_tile);
    
}