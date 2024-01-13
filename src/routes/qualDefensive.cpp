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

    //go to elevation bars
    drive.turnRight(35_deg);
    drive.goBackward(35_in);
    
    OdomCustom::setPos(0_in, 0_in);
    drive.faceToPoint({20_tile, 0_tile}, true, {{0, 0.8}});

    drive.goBackward(1.2_tile, {{0, 0.7}});


    // auto outreach_param = 12_in;

    // drive.goForward(outreach_param);
    // drive.goBackward(1_tile + outreach_param + 6_in, {{0, 0.7}});

    // drive.turnLeft(42_deg, {{0, 0.7}});
    // eff.wingsToggle();
    // // get the ball out of preload zone
    // drive.goBackward(20_in, {}, {{0.75, [](){
    //     eff.wingsToggle();
    // }}});

    // pros::delay(300);
    // drive.turnLeft(45_deg);
    // pros::delay(300);
    // drive.turnRight(180_deg);

    // auto dist_param = 8_in;    

    // drive.setToleranceParams(nullopt, nullopt, 1_s);
    // eff.setIntake(true, false);
    // drive.goForward(dist_param);
    // drive.goBackward(dist_param);
    // drive.turnLeft(180_deg);
    
    // // SLAM
    // drive.moveArcade(-1, 0);
    // pros::delay(2000); 
    // drive.moveArcade(0,0);
    // pros::delay(100);

    // drive.setToleranceParams(nullopt, nullopt, 1_s);
    // drive.goForward(dist_param);    

    // eff.setIntake(false, true);
    
}