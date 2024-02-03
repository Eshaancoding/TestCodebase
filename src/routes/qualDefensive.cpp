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
    drive.setToleranceParams(nullopt, nullopt, 1.3_s);
    drive.goForward(16.5_in, {}, {{0.9, [](){
        eff.wingsToggle();
    }}});
    eff.wingsToggle();
    drive.resetToleranceParams();
    pros::delay(500);
    drive.turnLeft(25_deg, {{0, 0.85}});

    //score two triballs
    eff.setIntake(true, false);
    // drive.setToleranceParams(nullopt, nullopt, 1_s);
    // drive.goForward(2.2_tile, {{0, 1.4}}, {{0.7, [](){
    //     eff.setIntake(true, false);
    // }}});
    // drive.resetToleranceParams();
    drive.moveArcade(1, 0);
    pros::delay(600);

    drive.moveArcade(-0.5, 0);
    pros::delay(300);
    drive.turnLeft(180_deg);
    pros::delay(100);

    drive.moveArcade(-1, 0);
    pros::delay(600);
    drive.moveArcade(0, 0);

    drive.goForward(3_in);
    eff.setIntake(false, true);

    drive.faceToPoint({-20_tile, 0_tile}, true);
    
    drive.setToleranceParams(nullopt, nullopt, nullopt, 0);
    drive.goForward(2.1_tile);

    drive.resetToleranceParams();
    drive.setToleranceParams(nullopt, nullopt, 1.5_s);
    eff.wingsToggle();
    drive.turnRight(30_deg, {{0, 0.6}});
    drive.resetToleranceParams();
}