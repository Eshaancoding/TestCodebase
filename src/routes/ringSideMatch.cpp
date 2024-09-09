#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"   

void Routes::ringSideMatch () {
    OdomCustom::setPos(0_in, 0_in, 146_deg); // set our default/initial position
    drive.goBackward(1.803_tile);
    eff.toggleClamp(); 
    drive.turnLeft(101.31_deg);
    drive.goForward(1.414_tile);
    
    drive.turnRight(135_deg);
    eff.intakeToggle();
    drive.goForward(1_tile);
    drive.turnRight(63.435_deg);
    drive.goForward(2.236_tile);

    // 100% - Eshaan B.
    
    bool is_mogo = true;
    if (is_mogo) {
        // do mogo route!
    } else {
        // not do mogo route!
    }
}

// 1 tile = 12 inches