#include "routes.h"
#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::skills () {
    eff.wingsToggle();
    drive.goForward(16_in, {}, {{0.9, [](){
        eff.wingsToggle();
    }}});
    pros::delay(500);
    drive.turnRight(27_deg, {{0, 0.85}});

    eff.setIntake(true, false);
    drive.setToleranceParams(nullopt, nullopt, 1_s);
    drive.goForward(2.2_tile, {{0, 1.4}}, {{0.7, [](){
        eff.setIntake(true, false);
    }}});
    drive.resetToleranceParams();
    drive.goBackward(6_in);

    drive.turnLeft(45_deg);
    drive.goBackward(6_in);
    drive.turnRight(90_deg);

    eff.toggleShootingState();
    while (true) {
        eff.stepShootMotor();
        pros::delay(50);
    }
}