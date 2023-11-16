#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::left() {
    
    OdomCustom::setPos(0_in, 0_in, 45_deg);
    
    eff.intakeToggle();
    eff.wingsToggle();
    drive.goBackward(12_in, {}, {{0.6, [](){
        eff.wingsToggle();
    } }});
    drive.turnRight(145_deg);
    eff.intakeToggle(true); // reverse = always on
    
    // AY SLAM THAT 
    drive.setToleranceParams(nullopt, nullopt, 1_s);
    drive.goForward(0.8_tile);

    // turn back, return, then turn again
    drive.setToleranceParams(nullopt, nullopt, 0.75_s);
    drive.goBackward(10_in);
    drive.resetToleranceParams();
    eff.intakeToggle();
    drive.turnRight(180_deg);
    drive.setToleranceParams(nullopt, nullopt, 1_s);
    drive.goBackward(1_tile, {{0, 1.1}});
    
    // slam that shit again
    drive.goForward(8.5_in);
    drive.resetToleranceParams();

    OdomCustom::setPos(0_in, 0_in);
    drive.faceToPoint({-10_in, 0_in}, false, {{0, 0.9}});  

    OdomCustom::setPos(0_in, 0_in, 90_deg);
    drive.goBackward(2.4_tile, {}, {{0.8, [](){
        eff.wingsToggle();
    }}});

    drive.setToleranceParams(nullopt, nullopt, 1.5_s);
    drive.turnRight(20_deg);
    drive.resetToleranceParams();

    
    // eff.wingsToggle();
    // drive.turnLeft(90_deg);
    // eff.wingsToggle();
    // drive.goForward(2_tile);
}