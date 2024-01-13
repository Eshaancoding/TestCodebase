#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::elimOffensive() {

    OdomCustom::setPos(0_in, 0_in, 45_deg);

    eff.setIntake();
    drive.goForward(76_in, {{0, 1.7}, {0.7, 0.6}});
    drive.setToleranceParams(nullopt, nullopt, 2_s);
    drive.turnLeft(135_deg);
    eff.setIntake(true, false);
    pros::delay(500);
    eff.setIntake();

    // slam
    eff.wingsToggle();
    drive.setToleranceParams(nullopt, nullopt, 1.7_s);
    drive.goForward(2.2_tile, {{0, 1.4}}, {{0.7, [](){
        eff.setIntake(true, false);
    }}});
    drive.resetToleranceParams();
}