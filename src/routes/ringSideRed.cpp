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
        drive.goForward(0.25_tile); // grabs mogo

        drive.setToleranceParams(std::nullopt, std::nullopt, 1_s, std::nullopt);
        !eff.isBlue.load() ? drive.turnRight(135_deg) : drive.turnLeft(135_deg);
        drive.resetToleranceParams(); // faces wall stake rings

        eff.setIntake(IntakeState::INTAKE);
        drive.goForward(0.8_tile); // grabs wall stake rings

        drive.setToleranceParams(std::nullopt, std::nullopt, 1_s, std::nullopt);
        !eff.isBlue.load() ? drive.turnLeft(40_deg) : drive.turnRight(40_deg);
        drive.resetToleranceParams(); 

        drive.goForward(0.8_tile); // grabs the other wall stake ringring 

        drive.setToleranceParams(std::nullopt, std::nullopt, 1_s, std::nullopt);
        !eff.isBlue.load() ? drive.turnLeft(10_deg) : drive.turnRight(10_deg);
        drive.resetToleranceParams(); // faces the ring next to wall stake rings

        drive.goForward(0.3_tile);
        pros::delay(300);
        drive.goBackward(0.5_tile); // grabs ring
        
        drive.setToleranceParams(std::nullopt, std::nullopt, 1.5_s, std::nullopt);
        drive.faceToPoint({0_in, 10_tile}, true);
        drive.resetToleranceParams(); // face alliance stake ring

        drive.goForward(1_tile);
        pros::delay(500);
        drive.goBackward(0.25_tile); // grabs ring
        !eff.isBlue.load() ? drive.turnLeft(90_deg) : drive.turnRight(90_deg);
        drive.goForward(1.8_tile); // touches ladder
        eff.toggleClamp(); // drops clamp
        eff.setIntake(IntakeState::INACTIVE);
   
}