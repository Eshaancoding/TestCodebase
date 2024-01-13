#include "routes.h"
#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::skills () {
    drive.setToleranceParams(nullopt, nullopt, 0.5_s);
    drive.goForward(16_in);
    pros::delay(500);
    drive.turnRight(27_deg);

    eff.setIntake(true, false);
    drive.setToleranceParams(nullopt, nullopt, 1_s);
    drive.goForward(2.2_tile, {{0, 1.4}}, {{0.7, [](){
        eff.setIntake(true, false);
    }}});
    drive.resetToleranceParams();
    drive.goBackward(6_in);

    eff.setIntake(false, true);

    drive.turnLeft(45_deg);
    drive.goBackward(12_in);
    drive.turnRight(130_deg);

    drive.setToleranceParams(nullopt, nullopt, 1_s);
    drive.goBackward(8_in, {{0, 1.4}});
    drive.resetToleranceParams();

    // move left side back
    drive.moveTank(-0.5, 0);
    pros::delay(600);
    drive.moveTank(0, 0);

    eff.toggleShootingState();
    while (true) {
        eff.stepShootMotor();
        pros::delay(50);
    }
}