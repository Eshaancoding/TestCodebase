#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"
#include <optional>

void lilRoute (bool reverse = false) {
    drive.setToleranceParams(std::nullopt, std::nullopt, 1.0_s, std::nullopt);
    drive.faceToPoint({3_tile, 0_in}, true);
    drive.setToleranceParams(std::nullopt, std::nullopt, 1.3_s, std::nullopt);
    drive.goBackward(1.5_tile);
    drive.resetToleranceParams();

    eff.toggleClamp(); //clamp on
    eff.setIntake(IntakeState::INTAKE);
    drive.goPath({
        Path({0_in, 0_in}),
        Path({0.75_tile, (reverse ? -1 : 1) * -0.5_tile}),
        Path({2.35_tile, (reverse ? -1 : 1) * -1.62_tile}) // 2.3
    }, 5_in, 5_in);

    pros::delay(500);

    drive.goBackward(0.24_tile);

    drive.faceToPoint({-1_tile, (reverse ? -1 : 1) * 0.5_tile}, true);

    drive.goPath({
        Path({0_in, 0_in}),
        Path({-1_tile, (reverse ? -1 : 1) * 0.22_tile}),
        Path({-2.4_tile, (reverse ? -1 : 1) * 0.22_tile})
    }, 5_in, 5_in, false, 3_s);

    pros::delay(500);

    drive.moveArcade(-0.2, 0);
    pros::delay(300);
    drive.moveArcade(0, 0);


    drive.faceToPoint({50_tile, (reverse ? -1 : 1) * -70_tile}, true);

    drive.goForward(0.7_tile);

    drive.faceToPoint({20_tile, (reverse ? -1 : 1) * 5_tile}, true);
    drive.moveArcade(-0.5, 0);
    pros::delay(500);
    drive.moveArcade(0, 0);

    eff.toggleClamp(); //clamp off
    eff.setIntake(IntakeState::INACTIVE);
}

void Routes::skills () {
    OdomArc::setPos(0_in, 0_in, 90_deg);
    eff.setIntake(IntakeState::INTAKE); 
    pros::delay(600);

    drive.goPath({ // REALLY REALLY REALLY TUNABLE!!!
        Path({0_in, 0_in}),
        Path({0.4_tile, 0_in}),
        Path({1.9_tile, -1.25_tile})
    }, 5_in, 5_in); // don't have to be too accurate!
    
    eff.setIntake(IntakeState::INACTIVE);

    drive.goBackward(0.4_tile);
    lilRoute();

    drive.goForward(0.1_tile);
    drive.faceToPoint({20_tile, 0_tile}, true);
    drive.goForward(0.8_tile);
    drive.faceToPoint({0_tile, 20_tile}, true);
    drive.goForward(2.8_tile);
    drive.turnRight(45_deg);
    
    eff.setIntake(IntakeState::INTAKE);
    drive.goForward(1.3_tile);
    eff.setIntake(IntakeState::INACTIVE);
    drive.goBackward(0.2_tile);
    pros::delay(300);

    lilRoute(true);

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
}