#include "routes.h"
#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::skills () {
    OdomCustom::setPos(0_in, 0_in, -135_deg);

    drive.setToleranceParams(nullopt, nullopt, 1.4_s);
    drive.goToPoint({-4_tile, -2_tile}, true, false, {{0, 1.35}});
    drive.resetToleranceParams();
    drive.moveTank(0, 0);
    // pros::delay(100);

    // // move one motor side
    drive.moveTank(0, -0.7);
    pros::delay(600);
    drive.moveTank(0, 0);


    eff.toggleFourBar();
    pros::delay(500);
    eff.slapper.move_velocity(200);
    eff.smallerSlapper.move_velocity(-200);
    pros::delay(100);
    eff.slapper.move_velocity(0);
    eff.smallerSlapper.move_velocity(0);
    pros::delay(100);
    eff.slapper.move_velocity(200);
    eff.smallerSlapper.move_velocity(-200);
    pros::delay(500);

    // drive.turnLeft(45_deg);
    
    // drive.faceToPoint({-10_tile, -10_tile}, true);
    // drive.goBackward(12_in);
    // drive.faceToPoint({-5_tile, 50_tile}, true);

    // drive.setToleranceParams(nullopt, nullopt, 1_s);
    // drive.goBackward(8_in, {{0, 1.4}});
    // drive.resetToleranceParams();

    // // move left side back
    // drive.moveTank(-0.5, 0);
    // pros::delay(600);
    // drive.moveTank(0, 0);

    // eff.toggleShootingState();
    // while (true) {
    //     eff.stepShootMotor();
    //     pros::delay(50);
    // }
}