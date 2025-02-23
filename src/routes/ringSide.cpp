#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

//ringside rush
void Routes::ringSide () {
    OdomArc::setPos(0_in, 0_in, -90_deg); // set our default/initial position
    //bool is_blue = (eff.isBlue).load();
    bool is_blue = false; 

    eff.toggleBoinker();
    drive.goPath({
        Path({0_tile, 0_tile}),
        Path({-1.7_tile, 0_tile}),
        Path({-2.2_tile, -0.2_tile})
    }, 5_in, 5_in);
    
    drive.faceToPoint({0_tile, -1_tile},true); // face mogo
    
    // drive.setToleranceParams(std::nullopt, 3_in); // cjange d tolerance to 1_in
    // drive.goBackward(1.53_tile, {{0, 0.9}}); // go back towards mogo og .7
    // drive.resetToleranceParams(); // go back to 0.5_in. 
    // eff.toggleClamp(); // clmap mogo
    // drive.faceToPoint({0_tile, -1_tile}, true);
    // eff.toggleBoinker();

    // eff.toggleIntakeState(INTAKE); // intake
    // drive.goForward(1.2_tile);

    // drive.turnLeft(150_deg);
    // drive.goForward(1.7_tile);
    // drive.turnLeft(110_deg);
    // drive.goForward(0.5_tile);
    // eff.toggleClamp();
    // eff.setIntake(IntakeState::INACTIVE);


    // IGNORE BELOW
    // eff.arm_state = ArmState::PID_ARM;
    // eff.currentState = State::hasDonut;

    // drive.setToleranceParams(std::nullopt, 2_in); // no changes to time tolerance, but distance tolerance is set to 1_in
    // drive.goForward(1.78_tile, {{0, 0.6}}); // go towards ladder, make this slower 
    // drive.resetToleranceParams();

    // eff.raiseArm();
    // pros::delay(500);
    // eff.stopArm();
    
    // drive.goForward(1.5_tile); // intake both rings
    // drive.turnRight(90_deg);
    // drive.goForward(0.75_tile);
    // //drive.faceToPoint({0_tile,-2_tile}, true); // turn towards ladder
    // drive.turnRight(160_deg);
    // drive.goForward(2.5_tile); // touch ladder
    // eff.toggleClamp();
   
}