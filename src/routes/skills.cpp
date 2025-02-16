#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"
#include <optional>

void lilRoute (bool reverse = false) {
    /*
    drive.setToleranceParams(1.0_s,std::nullopt, std::nullopt, std::nullopt);
    drive.faceToPoint({3_tile, 0_in}, true); // face clamp
    drive.setToleranceParams( 1.3_s,std::nullopt, std::nullopt, std::nullopt);
    drive.goBackward(1.65_tile);
    drive.resetToleranceParams();

    eff.toggleClamp(); //clamp on
    eff.setIntake(IntakeState::INTAKE);

    // initial sweep of rings
    drive.goPathDepr({
        PathDepr({0_in, 0_in}),
        PathDepr({0.75_tile, (reverse ? -1 : 1) * -0.5_tile}),
        PathDepr({2.35_tile, (reverse ? -1 : 1) * -1.62_tile}) // 2.3
    }, 5_in, 5_in);

    pros::delay(500);

    drive.goBackward(0.24_tile);

    drive.setToleranceParams(1.5_s);
    drive.faceToPoint({-1_tile, (reverse ? -1 : 1) * 0.5_tile}, true);
    drive.resetToleranceParams();

    // drive to that path to just sweep in multiple mogos while intaking
    drive.goPathDepr({ // second sweep near corner grabs 2 rings
        PathDepr({0_in, 0_in}),
        PathDepr({-1_tile, (reverse ? -1 : 1) * 0.25_tile}),
        PathDepr({-2.4_tile, (reverse ? -1 : 1) * 0.22_tile})
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

    */
}

// complex lil route is basically the route but we are doing wall stakes :D
void ComplexLilRoute (bool reverse = false) {
    /*
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

    */
}

void Routes::skills () {

	drive.move({
		DrivePoint({0.1738_tile, 2.9979_tile}, 0.3_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({0.4221_tile, 2.9897_tile}, 0.3_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({0.6621_tile, 2.8903_tile}, 0.3_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({0.8441_tile, 2.7662_tile}, 0.3_tile, 2.5_tps, 20.42, nullopt),
		DrivePoint({2.251_tile, 1.7483_tile}, 0.3_tile, 2.5_tps, 20.42, nullopt),
	});


}