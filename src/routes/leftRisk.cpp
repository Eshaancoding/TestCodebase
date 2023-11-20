#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::leftRisky () {
    while (true) {
        eff.resetCata();
        if (eff.state == CataState::SHOOTING) { 
            break;
        }
        pros::delay(20);
    }
     
    OdomCustom::setPos(0_in, 0_in, -135_deg);
    eff.wingsToggle();
    eff.setIntake();
    
    // get the ball out of preload zone
    drive.goBackward(12_in, {{0, 0.7}}, {{0.7, [](){
        eff.wingsToggle();
    }}});

    drive.turnLeft(70_deg, {{0, 0.7}});
    
    eff.cataOne.move_velocity(100);
    eff.cataTwo.move_velocity(-100);
    pros::delay(300); 
    eff.cataOne.move_velocity(0);
    eff.cataTwo.move_velocity(0);

    eff.setIntake(false, false);
}

