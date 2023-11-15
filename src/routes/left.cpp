#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::left() {
    eff.intakeToggle();
    eff.wingsToggle();
    drive.goBackward(12_in, {}, {{0.6, [](){
        eff.wingsToggle();
    } }});
    drive.turnRight(145_deg);
    eff.intakeToggle(true);
    drive.goForward(0.8_tile);

    eff.intakeToggle();
    drive.goBackward(10_in);

    OdomCustom::setPos(0_in, 0_in);
    drive.faceToPoint({-10_in, 0_in}, false);  

    drive.goBackward(2.5_tile, {}, {{0.8, [](){
        eff.wingsToggle();
    }}});
    drive.turnRight(10_deg);

    
    // eff.wingsToggle();
    // drive.turnLeft(90_deg);
    // eff.wingsToggle();
    // drive.goForward(2_tile);
}