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
    bool is_blue = (eff.isBlue).load();
    //bool is_blue = false;

    eff.toggleBoinker();
    eff.toggleIntakeState(INTAKE);
    drive.goPath({ // turn towards 4 stack ring
        Path({0_tile,0_tile}),
        Path({0_tile, 1.15_tile}),
        Path({is_blue ? 0.33_tile : -0.33_tile, 1.69_tile})
    }, 5_in,5_in); 
    pros::delay(600);
    eff.toggleIntakeState(INACTIVE);    
    
    // drive.faceToPoint({1.5_tile,1_tile},true); // face mogo
    //OdomArc::setPos(0_tile, 0_tile, -45_deg);
    drive.setToleranceParams(std::nullopt, 3_in); // cjange d tolerance to 1_in
    drive.goBackward(1.53_tile, {{0, 0.9}}); // go back towards mogo og .7
    drive.resetToleranceParams(); // go back to 0.5_in. 
    eff.toggleBoinker();
    eff.toggleClamp(); // clmap mogo

    eff.toggleIntakeState(INTAKE); // intake
    drive.goPath({
        Path({0_tile,0_tile}),
        Path({is_blue ? 0.5_tile : -0.5_tile,0.4_tile}),
        Path({is_blue ? 1.5_tile : -1.5_tile, 0.7_tile})
    }, 5_in, 5_in);

    drive.setToleranceParams(1_s);
    is_blue ? drive.turnRight(90_deg) : drive.turnLeft(90_deg); // turn towards rings DO PP HERE
    drive.resetToleranceParams();
    drive.goForward(1.58_tile);
    is_blue ? drive.turnRight(135_deg) : drive.turnLeft(135_deg);
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