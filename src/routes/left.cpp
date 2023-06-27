#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"

void Routes::left() {
    /**
     * Hi priya, a few things/tips:

     * use goForward, goBackward, turnLeft, or turnRight. Don't use goToPoint, etc. Has weird coordinate system that's pretty weird

     * factor map: basically changes the how fast/slow the robot goes. there's two params. The first one determines what percentage of the path the factor should activate
        * ex:, if the first param is 0 and the second param is 0.5, then the the start of the path it will go 50% speed
        * ex: if the first param is 0.25 and the second param is 0.75, then at 25% of the path it will start to go 75% speed until the path is done

     * callback map: basically calls a function after reaches a certain % of path
        * ex: if the first param is 0.5 and the second is effectors.outtake(), then at 50% of the path it will start calling the effectors.outtake() functon (only called once)
        * note that if you want to have only a callback map and not a factor map, then you may have to do something like goForward(2_in, {}, {{0.5, func()}}). The {} in the middle indicates empty factor map (i.e factor stays the same: 1)

     * effectors.enablePiston() = enable piston boost (shoots disk with more power). DisablePiston does the opposite

     * also note that sometimes the angles are weird, you may have to tune them. (for example 83 degrees is really suppose to be 90 but odom can mess up pretty easily so 83 is there to compensate for that)

     * if the robot oscillates a little, then maybe adding a decreased factor (i.e make the robot go at 75% speed by adding {{0, 0.75}} to the factor map parameter)

     * GL :) 
     */

    effectors.disablePiston();
    // sets position
    odometery.setPos({14_in, 108_in, 180_deg});
    
    // reset cata
    while (true) {
        effectors.stepCataReset();
        pros::delay(10);
        if (effectors.shouldReset == false) break;
    }
    
    // spin roller    
    drive.goForward(4_in, {{0, 1}}, {{0.5, [](){
        effectors.outtake();
    } }} );
    effectors.delay(50_ms);
    effectors.stopIntake();
    drive.goBackward(6_in);
    
    // go to middle point
    drive.turnLeft(130_deg, {{0, 0.75}});
    drive.setToleranceParams(std::nullopt, std::nullopt, 3_s);
    drive.goForward(2.6_tile, {{0, 1}});
    drive.resetToleranceParams();
    
    // shoot disk!
    drive.turnRight(85_deg);
    effectors.enablePiston();
    drive.goBackward(3_in, {}, {{0.5, [](){
        effectors.shoot();
    }}});
    effectors.delay(100_ms);
    effectors.disablePiston();

    // exit out of shooting position and turn and go to other roller
    drive.goForward(7_in);
    drive.turnLeft(83_deg, {{0, 0.75}});
    drive.setToleranceParams(std::nullopt, std::nullopt, 3_s);
    drive.goForward(2.55_tile, {{0, 1}});
    drive.resetToleranceParams();

    // go forward a little to touch roller
    drive.turnRight(40_deg);
    drive.setToleranceParams(std::nullopt, std::nullopt, 1.5_s);
    drive.goForward(7_in, {{0, 0.75}} );
    drive.resetToleranceParams();

    // spin the roller
    effectors.outtake();
    effectors.delay(350_ms);
    effectors.stopIntake();

    // cata reset
    while (true) {
        effectors.stepCataReset();
        pros::delay(10);
        if (effectors.shouldReset == false) break;
    }
}