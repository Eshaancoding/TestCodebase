#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"   

void Routes::mogoSideMatch () {
    OdomCustom::setPos(0_in, 0_in, 0_deg); // set our default/initial position
    eff.toggleClamp();

    drive.setToleranceParams(std::nullopt, std::nullopt, 1.5_s, std::nullopt);
    drive.goBackward(1.65_tile, {}, {{0.8, [](){
        // eff.toggleClamp();
        printf("Clamped!\n");
    }}});
    eff.toggleClamp();
    
    drive.turnRight(62.435_deg);
    eff.setIntakeState(IntakeState::INTAKE);
    drive.goForward(1_tile);

    bool isRush = false;
    if (isRush){ // we are almost certaintly not doing rush
        // pros::delay(1000);
        // eff.toggleClamp();
        // eff.intakeToggle();
        // drive.turnLeft(90_deg);
        // drive.goBackward(1_tile);
        // eff.toggleClamp();
        // drive.goForward(1.5_tile);
    } else{
        drive.turnLeft(155.435_deg, {{0, 0.8}});
        pros::delay(100);
        drive.goForward(2.136_tile, {{0, 0.8}});
    }
}