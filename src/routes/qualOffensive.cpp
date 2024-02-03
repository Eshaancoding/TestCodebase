#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::qualOffensive() {
    
    OdomCustom::setPos(0_in, 0_in, 45_deg);
    
    // go back to get the triball out
    eff.setIntake();
    drive.goBackward(10_in);
    eff.wingsToggle();
    
    drive.goForward(10_in, {}, {{0.5, [](){
        eff.wingsToggle();
    }}});
    
    // set the triball into the our goal
    drive.turnLeft(160_deg, {{0, 0.8}});
    
    // slam
    eff.setIntake(true, false);
    drive.moveArcade(1, 0);
    pros::delay(800);
    drive.moveArcade(0, 0);
    pros::delay(200);
    eff.setIntake(false, true);

    // go a little bit back 
    drive.goBackward(3_in);
    drive.faceToPoint({0_tile, 20_tile}, true);

    drive.setToleranceParams(nullopt, nullopt, nullopt, 0);
    drive.goForward(2.1_tile);
    drive.resetToleranceParams();

    drive.setToleranceParams(nullopt, nullopt, 1.5_s);
    eff.wingsToggle();
    drive.turnLeft(30_deg, {{0, 0.6}});
    drive.resetToleranceParams();
}