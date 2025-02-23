#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"
#include <optional>

void lilRoute (bool reverse = false) {
    drive.setToleranceParams(1.0_s,std::nullopt, std::nullopt, std::nullopt);
    drive.faceToPoint({3_tile, 0_in}, true); // face clamp
    drive.setToleranceParams( 1.3_s,std::nullopt, std::nullopt, std::nullopt);
    drive.goBackward(1.65_tile);
    drive.resetToleranceParams();

    eff.toggleClamp(); //clamp on
    eff.setIntake(IntakeState::INTAKE);

    // initial sweep of rings
    drive.goPath({
        Path({0_in, 0_in}),
        Path({0.75_tile, (reverse ? -1 : 1) * -0.5_tile}),
        Path({2.35_tile, (reverse ? -1 : 1) * -1.62_tile}) // 2.3
    }, 5_in, 5_in);

    pros::delay(500);

    drive.goBackward(0.24_tile);

    drive.setToleranceParams(1.5_s);
    drive.faceToPoint({-1_tile, (reverse ? -1 : 1) * 0.5_tile}, true);
    drive.resetToleranceParams();

    // drive to that path to just sweep in multiple mogos while intaking
    drive.goPath({ // second sweep near corner grabs 2 rings
        Path({0_in, 0_in}),
        Path({-1_tile, (reverse ? -1 : 1) * 0.25_tile}),
        Path({-2.4_tile, (reverse ? -1 : 1) * 0.22_tile})
    }, 5_in, 5_in, false, 3_s);

    pros::delay(500);

    // go back just a little bit away from wall
    drive.moveArcade(-0.2, 0);
    reverse ? pros::delay(130) : pros::delay(130);
    drive.moveArcade(0, 0);

    // face to last ring
    drive.setToleranceParams(1.5_s); // MAKE THIS FASTER
    drive.faceToPoint({50_tile, (reverse ? -1 : 1) * -64_tile}, true, {{0, 0.8}}); // go a little bit slower to not move to much. 
    drive.resetToleranceParams();

    // go forward to last ring
    drive.goForward(0.7_tile);

    // face to mogo dump (clamp facing corner)
    drive.setToleranceParams(1.5_s);
    drive.faceToPoint({20_tile, (reverse ? -1 : 1) * 5_tile}, true);
    drive.resetToleranceParams();

    // mogo dump (back into corner)
    drive.moveArcade(-0.5, 0);
    pros::delay(500);
    drive.moveArcade(0, 0);

    eff.toggleClamp(); //drop mogo in corner
    eff.setIntake(IntakeState::INACTIVE);
}

// complex lil route is basically the route but we are doing wall stakes :D
void ComplexLilRoute (bool reverse = false) {
    drive.setToleranceParams(1.0_s,std::nullopt, std::nullopt, std::nullopt);
    drive.faceToPoint({3_tile, 0_in}, true);
    drive.setToleranceParams( 1.3_s,std::nullopt, std::nullopt, std::nullopt);
    drive.goBackward(1.2_tile);
    drive.resetToleranceParams();

    eff.toggleClamp(); //clamp on
    eff.setIntake(IntakeState::INTAKE);

    // ================= this is being changed ============ 
    drive.faceToPoint({3_tile, -1_tile}, true);
    drive.goForward(3.162_tile);
    pros::delay(500);

    drive.faceToPoint({20_tile, 0_tile}, true);
    drive.goBackward(0.75_tile);
    drive.turnRight(90_deg);
    
    // ready arm
    while (true) {
        eff.arm_state = ArmState::PID_ARM;
        eff.currentState = State::isRaising;
        eff.stepArm();
        if (eff.arm_state == ArmState::IDLE_ARM) {
            break;
        }
        pros::delay(50);
    }
    
    drive.goForward(0.5_tile);
    pros::delay(750);
    eff.setIntake(IntakeState::INACTIVE);

    // dump then reset
    eff.armRight.move_voltage(12000);
    pros::delay(500);
    eff.armRight.move_voltage(0);
    pros::delay(500);
    eff.armRight.move_voltage(-8000);
    pros::delay(500);
    eff.armRight.move_voltage(0);

    // drive.goBackward(0.24_tile);

    // drive.setToleranceParams(1.5_s);
    // drive.faceToPoint({-1_tile, (reverse ? -1 : 1) * 0.5_tile}, true);
    // drive.resetToleranceParams();

    // // drive to that path to just sweep in multiple mogos while intaking
    // drive.goPath({
    //     Path({0_in, 0_in}),
    //     Path({-1_tile, (reverse ? -1 : 1) * 0.22_tile}),
    //     Path({-2.4_tile, (reverse ? -1 : 1) * 0.22_tile})
    // }, 5_in, 5_in, false, 3_s);

    // pros::delay(500);

    // // go back just a little bit
    // drive.moveArcade(-0.2, 0);
    // pros::delay(300);
    // drive.moveArcade(0, 0);

    // // face to last ring
    // drive.setToleranceParams(1.5_s);
    // drive.faceToPoint({50_tile, (reverse ? -1 : 1) * -70_tile}, true, {{0, 0.8}}); // go a little bit slower to not move to much. 
    // drive.resetToleranceParams();

    // // go forward to last ring
    // drive.goForward(0.7_tile);

    // // face to mogo dump
    // drive.setToleranceParams(1.5_s);
    // drive.faceToPoint({20_tile, (reverse ? -1 : 1) * 5_tile}, true);
    // drive.resetToleranceParams();

    // // mogo dump
    // drive.moveArcade(-0.5, 0);
    // pros::delay(500);
    // drive.moveArcade(0, 0);

    // eff.toggleClamp(); //clamp off
    // eff.setIntake(IntakeState::INACTIVE);
}

void Routes::skills () {
    OdomArc::setPos(0_in, 0_in, 45_deg);

    eff.arm_state = ArmState::Raising_ARM;
    pros::delay(1000);
    eff.currentState = State::IDLE; // drop ring on alliance stake
    eff.arm_state = ArmState::PID_ARM;

    drive.goBackward(0.5_tile);
    eff.toggleClamp(); // grab clamp
    
    drive.turnRight(130_deg); // face first ring (near ladder)
    eff.setIntake(IntakeState::INTAKE);
    drive.goForward(1_tile); // grab ring

    drive.turnRight(90_deg);
    drive.goForward(1_tile); // grab other ring

    drive.turnLeft(90_deg); // 90 deg left turn
    
    eff.changeState(); // raise to loading
    drive.goForward(1_tile); 
    drive.turnRight(90_deg); // face wall ring
    drive.goForward(0.25_tile); 
    eff.setIntake(IntakeState::INACTIVE); // grab wall ring

    eff.changeState();
    pros::delay(500);
    eff.changeState();
    pros::delay(500); // dump ring and back to idle

    drive.goBackward(0.25_tile); // back away

    // after you get wall stake
    drive.turnLeft(90_deg);
    eff.setIntake(IntakeState::INTAKE);
    drive.goForward(1_tile); // grab ring

    drive.turnLeft(180_deg);
    drive.goForward(4_tile);
    drive.goBackward(0.3_tile); // grab other 2 rings


    drive.turnLeft(90_deg);
    drive.goPath({
        Path({0_tile, 0_tile}),
        Path({0_tile, -0.5_tile}),
        Path({-0.5_tile, -1_tile})
    }); // turn back to nice spot

    drive.faceToPoint({0_tile, 3_tile}, true);
    drive.goForward(1.2_tile);

    drive.turnLeft(90_deg);
    drive.goBackward(1.1_tile);
    eff.toggleClamp();


    // after you dropped mogo in corner
    drive.faceToPoint({-4_tile, -2_tile}, true);



}


/* Old skills
 OdomArc::setPos(0_in, 0_in, 90_deg);
    eff.setIntake(IntakeState::INTAKE); 
    pros::delay(600);

    drive.goPath({ // REALLY REALLY REALLY TUNABLE!!!
        Path({0_in, 0_in}),
        Path({1.4_tile, -1.3_tile})
    }, 5_in, 5_in); // don't have to be too accurate!
    
    eff.setIntake(IntakeState::INACTIVE);

    drive.goBackward(0.15_tile); // note it doesn't go back??
    //ComplexLilRoute();
    lilRoute();

    drive.goForward(0.1_tile); // get out of corner

    drive.setToleranceParams(1_s);
    drive.faceToPoint({20_tile, 0_tile}, true); //turn to other side of field
    drive.resetToleranceParams();
    
    //drive.setToleranceParams(0.7_s);
    drive.goForward(0.73_tile); // go more forward in prep for turn to face other side
    //drive.resetToleranceParams();

    drive.setToleranceParams(1_s);
    drive.faceToPoint({0_tile, 20_tile}, true); 
    drive.resetToleranceParams();

    //drive.setToleranceParams(_s);
    drive.goForward(2.9_tile);  // go to toerh side
    //drive.resetToleranceParams();

    drive.setToleranceParams(1.5_s);
    drive.turnRight(45_deg);
    drive.resetToleranceParams();
    
    eff.setIntake(IntakeState::INTAKE);
    drive.goForward(1.3_tile);
    eff.setIntake(IntakeState::INACTIVE);
    drive.goBackward(0.2_tile);
    pros::delay(300);

    //ComplexLilRoute(false);
    lilRoute(true);

    OdomArc::setPos(0_in, 0_in, 0_deg);
    drive.goForward(2.4_tile);
    drive.faceToPoint({0.65_tile,1.1_tile}, true);

    eff.setIntake(IntakeState::SLOW);
    drive.goForward(1.65_tile);
    pros::delay(350);
    eff.setIntake(IntakeState::INACTIVE);
    drive.faceToPoint({-1.2_tile, -1.75_tile}, true);
    drive.setToleranceParams(std::nullopt, 5_in);
    drive.goBackward(1.23_tile);
    drive.resetToleranceParams();
    eff.toggleClamp(); // grab mogo
    pros::delay(250);

    eff.toggleIntakeState(INTAKE);
    drive.faceToPoint({0.8_tile, -1_tile}, true);
    drive.goPath({
        Path({0_tile,0_tile}),
        Path({1_tile, -0.75_tile}),
        Path({2.1_tile, -0.45_tile})
    });
    pros::delay(1000);
    drive.faceToPoint({-0.1_tile, 1_tile}, true);
    drive.goForward(1.25_tile);
    pros::delay(250);

    // face clamp to corner
    drive.faceToPoint({-0.5_tile, -0.4_tile}, true);
    drive.goBackward(2.2_tile);
    eff.toggleClamp();
    drive.goForward(1_tile);
    //drive.faceToPoint({-10_tile, 0_tile}, true);




    // drive.goBackward(1_tile);
    // eff.toggleClamp();
    // eff.intakeToggle();

    // // 
    // drive.goPath({
    //     Path({0_in, 0_in}),
    //     Path({1_tile, 0.3_tile}),
    //     Path({1.75_tile, 0.75_tile}),
    //     Path({2_tile, 1.5_tile})
    // });

    // drive.turnLeft(180_deg);
    // drive.goPath({
    //     Path({0_in, 0_in}),
    //     Path({-1_tile, -0.5_tile}),
    //     Path({-2.5_tile, -0.5_tile})
    // });

    // drive.faceToPoint({0.5_tile, 0.5_tile}, true);
    // drive.goForward(0.707_tile);
    // drive.faceToPoint({3_tile, -0.5_tile}, true);
    // drive.goBackward(1.118_tile);
    // eff.toggleClamp();
    
    // ======================================================
    // ============= third part of skills auton =============
    // ======================================================
    // eff.setIntake(false, true); // we are 1000% sure that our intake is off and we could use intakeToggle
    // drive.goForward(4.123_tile);
    // pros::delay(1500); //let ring go on intake
    // eff.intakeToggle(); //turn off
    // drive.faceToPoint({0_tile, -1_tile}, true);
    // eff.intakeToggle(); //turn on
    // drive.goForward(1_tile);
    // pros::delay(1000);
    // eff.intakeToggle();
    // drive.faceToPoint({-1_tile, 1_tile}, true);
    // drive.goBackward(1.414_tile);
    // eff.toggleClamp(); //clamp on
    // eff.intakeToggle(); //turn on, put rings on mogo
    // drive.faceToPoint({-1_tile, 1_tile}, true);
    // drive.goForward(1.414_tile);
    // drive.faceToPoint({0_tile, -1_tile}, true);
    // drive.goForward(1_tile);
    // drive.faceToPoint({2_tile, 0_tile}, true);
    // drive.goForward(1.5_tile);
    // drive.faceToPoint({-0.5_tile, 1_tile}, true); // weird
    // drive.goBackward(1.12_tile);
    // eff.toggleClamp(); //clamp off, mogo in corner
    // eff.intakeToggle(); //intake off
    // drive.faceToPoint({0_tile, 1_tile}, true);
    // drive.goForward(5_tile); //slam mogo in corner
*/