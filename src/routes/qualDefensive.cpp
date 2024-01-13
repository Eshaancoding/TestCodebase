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
    drive.goForward(17_in, {}, {{0.8, [](){
        eff.wingsToggle();
    }}});
    drive.turnLeft(30_deg, {{0, 0.7}});

    //score two triballs
    eff.setIntake(true, false);
    drive.setToleranceParams(nullopt, nullopt, 1.7_s);
    drive.goForward(2.2_tile, {{0, 1.4}}, {{0.7, [](){
        eff.setIntake(true, false);
    }}});
    drive.resetToleranceParams();
    drive.goBackward(6_in);
    eff.setIntake(false, true);

    //go to elevation bars
    drive.turnRight(35_deg);
    drive.goBackward(35_in);
    
    OdomCustom::setPos(0_in, 0_in);
    drive.faceToPoint({20_tile, 0_tile}, true, {{0, 0.8}});

    drive.goBackward(1.2_tile, {{0, 0.7}});

}