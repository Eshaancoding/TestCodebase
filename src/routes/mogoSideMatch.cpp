#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"   

void Routes::mogoSideMatch () {
    OdomCustom::setPos(0_in, 0_in, 123.69_deg); // set our default/initial position
    drive.goBackward(1.581_tile);
    eff.toggleClamp();
    drive.turnRight(63.435_deg);
    eff.intakeToggle();
    drive.goForward(1_tile);

    bool isRush = true;
    if (isRush){
        pros::delay(1000);
        eff.toggleClamp();
        eff.intakeToggle();
        drive.turnLeft(90_deg);
        drive.goBackward(1_tile);
        eff.toggleClamp();
        drive.goForward(1.5_tile);
    } else{
        drive.turnLeft(153.435_deg);
        drive.goForward(2.236_tile);
    }
}