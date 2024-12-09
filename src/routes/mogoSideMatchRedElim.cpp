#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"   

void Routes::mogoSideMatchRedElim () {
    OdomCustom::setPos(0_in, 0_in, 0_deg); // set our default/initial position
    eff.toggleClamp();

    drive.setToleranceParams(std::nullopt, std::nullopt, 1.5_s, std::nullopt);
    drive.goBackward(1.65_tile, {}, {{0.8, [](){
        // eff.toggleClamp();
        printf("Clamped!\n");
    }}});
    eff.toggleClamp();
    
    drive.turnLeft(61.435_deg);
    eff.setIntake(IntakeState::INTAKE);
    drive.goForward(1.3_tile);
    pros::delay(2000);
    drive.goBackward(0.3_tile);

    // drive.turnRight(75.435_deg);
    // drive.goForward(2.7_tile);
}