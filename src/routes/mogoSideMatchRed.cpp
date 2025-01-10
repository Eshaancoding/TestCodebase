#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

void Routes::mogoSideMatchRed () {
    OdomArc::setPos(0_in, 0_in, 0_deg); // set our default/initial position
    eff.toggleClamp();

    drive.setToleranceParams(std::nullopt, std::nullopt, 1.5_s, std::nullopt);
    drive.goBackward(1.65_tile, {}, {});
    eff.toggleClamp();
    drive.goForward(0.25_tile);
    
    drive.turnLeft(90_deg);
    eff.setIntake(IntakeState::INTAKE);
    drive.goForward(1.3_tile);

    drive.turnLeft(135_deg);

    pros::delay(500);
    drive.goForward(3_tile);
    eff.toggleClamp();
    eff.setIntake(IntakeState::INACTIVE);

    drive.turnRight(65_deg);
    drive.goBackward(1_tile);
    
}