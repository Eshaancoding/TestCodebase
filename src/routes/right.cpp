#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::right() {
    
    OdomCustom::setPos(0_in, 0_in, 45_deg);
    
    eff.setIntake();

    eff.wingsToggle();
    // get the ball out of preload zone
    drive.goBackward(12_in, {}, {{0.75, [](){
        eff.wingsToggle();
    }}});
    
    pros::delay(500);
    drive.turnRight(160_deg, {{0, 0.7}});
    
    // AY SLAM THAT 
    drive.setToleranceParams(nullopt, nullopt, 1_s);
    drive.goForward(0.8_tile);

    // turn back, return, then turn again
    drive.setToleranceParams(nullopt, nullopt, 0.75_s);

    eff.setIntake(true);
    drive.goBackward(10_in);
    eff.setIntake(false, true);

    // slam that shit again
    drive.resetToleranceParams();
    drive.turnRight(170_deg);
    drive.setToleranceParams(nullopt, nullopt, 1.2_s);
    drive.goBackward(1_tile, {{0, 1.4}});
    
    drive.goForward(7_in);
    drive.resetToleranceParams();

    OdomCustom::setPos(0_in, 0_in);
    drive.faceToPoint({-30_tile, 0_in}, false, {{0, 0.8}});  

    OdomCustom::setPos(0_in, 0_in, 90_deg);

    drive.setToleranceParams(nullopt, nullopt, 1.5_s);
    drive.goBackward(2.4_tile, {{0, 0.9}});

    drive.setToleranceParams(nullopt, nullopt, 1.5_s);
    drive.turnRight(20_deg, {}, {{0.5, [](){
        eff.wingsToggle();
    }}});
    drive.resetToleranceParams();
    
    // eff.wingsToggle();
    // drive.turnLeft(90_deg);
    // eff.wingsToggle();
    // drive.goForward(2_tile);
}