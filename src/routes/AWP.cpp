#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

void Routes::AWPRed () {
    eff.isBlue = false;

    OdomArc::setPos(0_in, 0_in, 0_deg); // set our default/initial position

    drive.goBackward(1.55_tile, {}, {});
    eff.toggleClamp();
    drive.goForward(0.25_tile);

    drive.setToleranceParams(1_s, std::nullopt, std::nullopt, std::nullopt);
    drive.turnLeft(135_deg);
    drive.resetToleranceParams();

    eff.setIntake(IntakeState::INTAKE);
    drive.goForward(0.8_tile);

    drive.setToleranceParams(1_s,std::nullopt, std::nullopt, std::nullopt);
    drive.turnRight(40_deg);
    drive.resetToleranceParams();

    drive.goForward(0.8_tile);

    drive.setToleranceParams(1_s,std::nullopt, std::nullopt, std::nullopt);
    drive.turnRight(10_deg);
    drive.resetToleranceParams();

    drive.goForward(0.3_tile);
    pros::delay(300);
    drive.goBackward(0.5_tile);
    
    drive.setToleranceParams(1.5_s, std::nullopt, std::nullopt, std::nullopt);
    drive.faceToPoint({0_in, 10_tile}, true);
    drive.resetToleranceParams();

    drive.goForward(1.6_tile);
    drive.turnRight(90_deg);
    drive.goForward(3_tile);
    eff.toggleClamp();
    eff.setIntake(IntakeState::INACTIVE);

    // =========== crossed line =========
    drive.faceToPoint({25_tile,-25_tile}, true);
    drive.goBackward(1.6_tile);
    eff.toggleClamp();
    eff.setIntake(IntakeState::INTAKE);

    drive.goForward(0.2_tile);
    drive.turnRight(135_deg);
    drive.goForward(1_tile);
    drive.turnRight(180_deg);
    drive.goForward(2_tile);
}