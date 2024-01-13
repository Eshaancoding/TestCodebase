#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::qualDefensive () {
    OdomCustom::setPos(0_in, 0_in, 45_deg);

    eff.setIntake();

    //get matchload triball out
    eff.wingsToggle();
    drive.goForward(16_in, {}, {{0.9, [](){
        eff.wingsToggle();
    }}});
    pros::delay(500);
    drive.turnLeft(27_deg, {{0, 0.85}});

    //score two triballs
    eff.setIntake(true, false);
    drive.setToleranceParams(nullopt, nullopt, 1_s);
    drive.goForward(2.2_tile, {{0, 1.4}}, {{0.7, [](){
        eff.setIntake(true, false);
    }}});
    drive.resetToleranceParams();
    drive.goBackward(6_in);
    eff.setIntake(false, true);

    drive.faceToPoint({-20_tile, 0_tile}, true);
    drive.goForward(2_tile);
    eff.wingsToggle();
    drive.setToleranceParams(nullopt, nullopt, 0.5_s);
    drive.turnRight(30_deg);
    drive.resetToleranceParams();

    //go to elevation bars
    // drive.turnRight(35_deg);
    // drive.goBackward(35_in);
    
    // OdomCustom::setPos(0_in, 0_in);
    // drive.faceToPoint({20_tile, 0_tile}, true);

    // drive.goBackward(1.3_tile, {{0, 1.2}});

}