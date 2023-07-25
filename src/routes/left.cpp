#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"

void Routes::left() {
    // effectors.disablePiston();
    // // sets position
    // odometery.setPos({14_in, 108_in, 180_deg});
    
    // // reset cata
    // while (true) {
    //     effectors.stepCataReset();
    //     pros::delay(10);
    //     if (effectors.shouldReset == false) break;
    // }

    // // spin roller    
    // drive.goForward(4_in);
    // effectors.outtake();
    // effectors.delay(300_ms);
    // effectors.stopIntake();
    // drive.goBackward(8_in);
    
    // // spin to face goal
    // drive.turnLeft(15_deg); 

    // // go forward & shoot
    // drive.goBackward(4_ft); 
    // effectors.delay(100_ms);
    // effectors.shoot();
    // effectors.delay(100_ms);

    // // go backward and face roller
    // drive.goForward(1_ft); // make sure that at this point it is aligned with the y-pos of the roller
    // drive.turnRight(105_deg); // this should now have the roller wheels aligned with the roller

    // // go forward until you reach roller
    // drive.goForward(10_ft, {{0, 1}}, {{0.5, [](){
    //     effectors.outtake();
    // } }} );
    // effectors.delay(300_ms);
    // effectors.stopIntake();
    // drive.goBackward(10_ft);

    // // now do expansion
    // drive.turnRight(135_deg);
    // drive.goForward(2_ft);
    // effectors.expand();
    // effectors.expand(false);

    // // cata reset
    // while (true) {
    //     effectors.stepCataReset();
    //     pros::delay(10);
    //     if (effectors.shouldReset == false) break;
    // }

    drive.goForward(6_in);
    drive.turnLeft(45_deg); 
    effectors.expand();
    effectors.expand(false);
}