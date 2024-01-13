#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::qualOffensive() {
    
    OdomCustom::setPos(0_in, 0_in, 45_deg);
    eff.setIntake();
    
    // go back to get the triball out
    drive.goBackward(10_in);
    eff.wingsToggle();
    
    drive.goForward(10_in, {}, {{0.5, [](){
        eff.wingsToggle();
    }}});
    
    // set the triball into the our goal
    drive.turnLeft(160_deg);
    
    // slam
    drive.setToleranceParams(nullopt, nullopt, 1.7_s);
    drive.goForward(2.2_tile, {{0, 1.4}}, {{0.7, [](){
        eff.setIntake(true, false);
    }}});
    drive.resetToleranceParams();

    // go a little bit back 
    drive.goBackward(8_in);
    eff.setIntake(false, true);

    drive.faceToPoint({0_tile, 20_tile}, true);
    drive.goForward(2_tile);
    eff.wingsToggle();
    drive.turnLeft(30_deg);

    // drive.turnLeft(45_deg);
    
    // // go backwawrd to the red bar zone
    // drive.goBackward(1.4_tile);
    // drive.turnLeft(43_deg);

    // // go backward to touch
    // drive.goBackward(1.2_tile, {{0, 0.7}});
}