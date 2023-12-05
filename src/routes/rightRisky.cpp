#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::rightRisky () {
    OdomCustom::setPos(0_in, 0_in, 45_deg);

    eff.setIntake(false, false);

    eff.wingsToggle();
    // get the ball out of preload zone
    drive.goBackward(14_in, {}, {{0.9, [](){
        eff.wingsToggle();
    }}});
    
    pros::delay(800);
    drive.turnRight(160_deg, {{0, 0.5}});
    
    // AY SLAM THAT 
    drive.setToleranceParams(nullopt, nullopt, 1_s);
    drive.goForward(0.8_tile);

    // turn back, return, then turn again
    drive.setToleranceParams(nullopt, nullopt, 0.75_s);

    eff.setIntake(true);
    drive.goBackward(8_in);
    eff.setIntake(false, true);

    OdomCustom::setPos(0_in, 0_in);
    drive.faceToPoint({-30_tile, 0_in}, false, {{0, 0.8}});  

    OdomCustom::setPos(0_in, 0_in, 90_deg);


}