#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

void Routes::mogoSideRed () {
    eff.isBlue = true;

    OdomArc::setPos(0_in, 0_in, 0_deg); // set our default/initial position

    drive.goBackward(1.65_tile, {}, {});
    eff.toggleClamp();
    drive.goForward(0.35_tile); // grab mogo
    
    drive.setToleranceParams(std::nullopt, std::nullopt, 1_s, std::nullopt);
    eff.isBlue.load() ? drive.turnRight(90_deg) : drive.turnLeft(90_deg);
    drive.resetToleranceParams();

    eff.setIntake(IntakeState::INTAKE);
    drive.goForward(1.3_tile); // grabs wall stake ring

    drive.setToleranceParams(std::nullopt, std::nullopt, 1.5_s, std::nullopt);
    eff.isBlue.load() ? drive.turnLeft(180_deg) : drive.turnRight(180_deg);
    drive.resetToleranceParams(); // faces ladder

    eff.toggleClamp(); // drops clamp
    eff.setIntake(IntakeState::INACTIVE);

    drive.goForward(1.6_tile); // touches ladder
}