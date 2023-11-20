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
    drive.goBackward(14_in, {}, {{0.6, [](){
        eff.wingsToggle();
    } }});
    drive.turnRight(145_deg);
    
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
    drive.faceToPoint({-30_tile, 0_in}, false, {{0, 0.9}});  

    OdomCustom::setPos(0_in, 0_in, 90_deg);

    drive.setToleranceParams(nullopt, nullopt, 1.5_s);
    drive.goBackward(2.4_tile);

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