#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::left() {
     
    OdomCustom::setPos(0_in, 0_in, -135_deg);
    eff.wingsToggle();
    eff.setIntake();
    
    // get the ball out of preload zone
    drive.goBackward(12_in, {}, {{0.7, [](){
        eff.wingsToggle();
    }}});
    
    // set the triball into the our goal
    drive.turnRight(15_deg);
    drive.setToleranceParams(nullopt, nullopt, 1_s);
    eff.setIntake(true);
    drive.goForward(20_in);
    drive.resetToleranceParams();

    // go back to the center.
    drive.goBackward(8_in);
    // OdomCustom::setPos(0_in, 0_in);
    drive.faceToPoint({-5_tile, -5_tile},true); // test if isRelative works
    drive.goBackward(1_tile);
    
    // put those triballs
    drive.faceToPoint({0_tile, -5_tile}, true);
    eff.wingsToggle();
    drive.goBackward(1_tile);
    eff.wingsToggle();
}