#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::leftRisky () {
    OdomCustom::setPos(0_in, 0_in, -135_deg);
    
    drive.goForward(8_in);
    

    eff.wingsToggle();
    eff.setIntake();
    
    // get the ball out of preload zone
    drive.goBackward(12_in, {}, {{0.7, [](){
        eff.wingsToggle();
    }}});
    
    // set the triball into the our goal
    drive.turnRight(20_deg);
    drive.setToleranceParams(nullopt, nullopt, 1.5_s);
    drive.goForward(2_tile);
    eff.setIntake(true);
    drive.resetToleranceParams();

    // go back to the center.
    drive.goBackward(8_in);
    drive.turnLeft(180_deg);
    eff.setIntake(false, true);

    drive.setToleranceParams(nullopt, nullopt, 1_s);
    drive.goBackward(10_in, {{0, 1.3}});
    drive.resetToleranceParams();

    drive.goForward(8_in);
    drive.faceToPoint({-5_tile, -5_tile},true);
    drive.setToleranceParams(nullopt, nullopt, 0.75_s);
    drive.goBackward(1.2_tile);
    drive.resetToleranceParams();
    
    // put those triballs
    drive.faceToPoint({0_tile, -5_tile}, true);

    // ===================== GO FORWARD ===================== 
    // figure this out   

}

