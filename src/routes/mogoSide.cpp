#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

void Routes::mogoSide () {

    OdomArc::setPos(0_in, 0_in, 1_deg); // set our default/initial position

    eff.toggleBoinker();
    drive.goForward(1.7_tile);
    // drive.goPath({ // turn to mogo
    //     Path({0_tile,0_tile}),
    //     Path({0_tile,1.9_tile}),
    //     Path({0.3_tile,2_tile})
    // });
    drive.goBackward(0.6_tile);
    eff.toggleBoinker();
    drive.goBackward(0.3_tile);

    drive.setToleranceParams(1_s);
    drive.faceToPoint({0_tile,-10_tile}, true);
    drive.resetToleranceParams();
    
    drive.goBackward(0.8_tile);
    eff.toggleClamp(); // got the first mogo
    eff.toggleIntakeState(INTAKE); // eat first donut
    eff.toggleClamp();


    drive.turnLeft(90_deg);
    drive.goForward(0.9_tile);
    eff.toggleIntakeState(INACTIVE);
    drive.turnRight(150_deg);
    drive.goBackward(1_tile);
    eff.toggleClamp();
    eff.toggleIntakeState(INTAKE);
    drive.turnLeft(180_deg);
    drive.goForward(0.5_tile);




    // drive.goBackward(1.5_tile, {}, {});
    // eff.toggleClamp();
    // drive.goForward(0.35_tile); // grab mogo
    
    // drive.setToleranceParams(std::nullopt, std::nullopt, 1_s, std::nullopt);
    // eff.isBlue.load() ? drive.turnRight(90_deg) : drive.turnLeft(90_deg);
    // drive.resetToleranceParams();

    // eff.setIntake(IntakeState::INTAKE);
    // drive.goForward(1.3_tile); // grabs wall stake ring

    // drive.setToleranceParams(std::nullopt, std::nullopt, 1.5_s, std::nullopt);
    // eff.isBlue.load() ? drive.turnLeft(180_deg) : drive.turnRight(180_deg);
    // drive.resetToleranceParams(); // faces ladder

    // eff.toggleClamp(); // drops clamp
    // eff.setIntake(IntakeState::INACTIVE);

    // drive.goForward(1.6_tile); // touches ladder
}