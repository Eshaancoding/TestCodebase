#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"   

void Routes::mogoSideMatchBlue () {
    OdomCustom::setPos(0_in, 0_in, 0_deg); // set our default/initial position
    eff.toggleClamp();

    drive.setToleranceParams(std::nullopt, std::nullopt, 1.5_s, std::nullopt);
    drive.goBackward(1.65_tile, {}, {{0.8, [](){
        // eff.toggleClamp();
        printf("Clamped!\n");
    }}});
    eff.toggleClamp();
    
    drive.turnRight(62.435_deg);
    eff.setIntake(IntakeState::INTAKE);
    drive.goForward(1_tile);

    drive.turnRight(185_deg);
    drive.goForward(2.0_tile);
    eff.toggleClamp();
    eff.setIntake(IntakeState::INACTIVE);
    pros::delay(500);
}