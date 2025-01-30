#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

//ringside rush
void Routes::ringSide () {
    OdomArc::setPos(0_in, 0_in, 0_deg); // set our default/initial position

    eff.toggleBoinker();
    drive.goForward(1.7_tile);
    drive.goPath({
        Path({0_tile,0_tile}),
        Path({-0.15_tile,2_tile}),
        Path({-0.3_tile,1.65_tile})
    });


    /*
    drive.goPath({ // REALLY REALLY REALLY TUNABLE!!!
        Path({0_in, 0_in}),
        Path({0.4_tile, 0_in}),
        Path({1.9_tile, -1.25_tile})
    }, 5_in, 5_in); // don't have to be too accurate!*/

    // drive.goBackward(1.5_tile, {}, {});
    // eff.toggleClamp();
    // drive.goForward(0.35_tile); // grabs mogo

    // drive.setToleranceParams(std::nullopt, std::nullopt, 1_s, std::nullopt);
    // !eff.isBlue.load() ? drive.turnRight(135_deg) : drive.turnLeft(135_deg);
    // drive.resetToleranceParams(); // faces wall stake rings

    // eff.setIntake(IntakeState::INTAKE);
    // drive.goForward(0.8_tile); // grabs wall stake rings

    // drive.setToleranceParams(std::nullopt, std::nullopt, 1_s, std::nullopt);
    // !eff.isBlue.load() ? drive.turnLeft(40_deg) : drive.turnRight(40_deg);
    // drive.resetToleranceParams(); 

    // drive.goForward(0.8_tile); // grabs the other wall stake ringring 

    // drive.setToleranceParams(std::nullopt, std::nullopt, 1_s, std::nullopt);
    // !eff.isBlue.load() ? drive.turnLeft(10_deg) : drive.turnRight(10_deg);
    // drive.resetToleranceParams(); // faces the ring next to wall stake rings

    // drive.goForward(0.3_tile);
    // pros::delay(300);
    // drive.goBackward(0.5_tile); // grabs ring
    
    // drive.setToleranceParams(std::nullopt, std::nullopt, 1.5_s, std::nullopt);
    // drive.faceToPoint({0_in, 10_tile}, true);
    // drive.resetToleranceParams(); // face alliance stake ring

    // drive.goForward(1_tile);
    // pros::delay(500);
    // drive.goBackward(0.25_tile); // grabs ring
    // !eff.isBlue.load() ? drive.turnLeft(90_deg) : drive.turnRight(90_deg);
    // drive.goForward(1.8_tile); // touches ladder
    // eff.toggleClamp(); // drops clamp
    // eff.setIntake(IntakeState::INACTIVE);
   
}