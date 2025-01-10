#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

void Routes::ringSideRed () {
    eff.isBlue = false;

    OdomArc::setPos(0_in, 0_in, 0_deg); // set our default/initial position

    drive.goBackward(1.55_tile, {}, {});
    eff.toggleClamp();
    drive.goForward(0.25_tile);

    drive.setToleranceParams(std::nullopt, std::nullopt, 1_s, std::nullopt);
    drive.turnLeft(135_deg);
    drive.resetToleranceParams();

    eff.setIntake(IntakeState::INTAKE);
    drive.goForward(0.8_tile);

    drive.setToleranceParams(std::nullopt, std::nullopt, 1_s, std::nullopt);
    drive.turnRight(40_deg);
    drive.resetToleranceParams();

    drive.goForward(0.8_tile);

    drive.setToleranceParams(std::nullopt, std::nullopt, 1_s, std::nullopt);
    drive.turnRight(10_deg);
    drive.resetToleranceParams();

    drive.goForward(0.3_tile);
    pros::delay(300);
    drive.goBackward(0.5_tile);
    
    drive.setToleranceParams(std::nullopt, std::nullopt, 1.5_s, std::nullopt);
    drive.faceToPoint({0_in, 10_tile}, true);
    drive.resetToleranceParams();

    drive.goForward(1_tile);
    pros::delay(500);
    drive.goBackward(0.25_tile);
    drive.turnRight(90_deg);
    drive.goForward(1.8_tile);
    eff.toggleClamp();
    eff.setIntake(IntakeState::INACTIVE);
}