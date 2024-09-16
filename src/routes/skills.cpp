#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"   

void Routes::skills () {
    OdomCustom::setPos(0_in, 0_in, 90_deg);
    eff.intakeToggle(); 
    pros::delay(1000);
    eff.intakeToggle(); //intake off

    drive.goPath({ // REALLY REALLY REALLY TUNABLE!!!
        Path({0_in, 0_in}),
        Path({1_tile, 0_in}),
        Path({2_tile, -1_tile})
    }); // don't have to be too accurate!

    drive.faceToPoint({3_tile, 0_in}, true);
    drive.goBackward(1_tile);
    eff.toggleClamp(); //clamp on
    drive.goPath({
        Path({0_in, 0_in}),
        Path({1_tile, -0.5_tile}),
        Path({2_tile, -1.5_tile})
    });

    drive.faceToPoint({-1_tile, 0.5_tile}, true);

    drive.goPath({
        Path({-0.5_tile, 0.5_tile}),
        Path({-1_tile, 0.5_tile}),
        Path({-2.5_tile, 0.5_tile})
    });
    

    drive.faceToPoint({0.5_tile, -0.5_tile}, true);
    drive.goForward(0.707_tile);
    drive.faceToPoint({1_tile, 0.5_tile}, true);
    drive.goBackward(1.118_tile);
    eff.toggleClamp(); //clamp off

    //second part skills auton
    drive.faceToPoint({1.75_tile, 3.75_tile}, true);
    eff.intakeToggle();
    drive.goForward(4.472_tile);
    pros::delay(500); // tunable 
    eff.intakeToggle();

    drive.faceToPoint({2_tile, 0_tile}, true);
    drive.goBackward(1_tile);
    eff.toggleClamp();
    eff.intakeToggle();

    // 
    drive.goPath({
        Path({0_in, 0_in}),
        Path({1_tile, 0.3_tile}),
        Path({1.75_tile, 0.75_tile}),
        Path({2_tile, 1.5_tile})
    });

    drive.turnLeft(180_deg);
    drive.goPath({
        Path({0_in, 0_in}),
        Path({-1_tile, -0.5_tile}),
        Path({-2.5_tile, -0.5_tile})
    });

    drive.faceToPoint({0.5_tile, 0.5_tile}, true);
    drive.goForward(0.707_tile);
    drive.faceToPoint({3_tile, -0.5_tile}, true);
    drive.goBackward(1.118_tile);
    eff.toggleClamp();
    
    // ======================================================
    // ============= third part of skills auton =============
    // ======================================================
    eff.setIntake(false, true); // we are 1000% sure that our intake is off and we could use intakeToggle
    drive.goForward(4.123_tile);
    pros::delay(1500); //let ring go on intake
    eff.intakeToggle(); //turn off
    drive.faceToPoint({0_tile, -1_tile}, true);
    eff.intakeToggle(); //turn on
    drive.goForward(1_tile);
    pros::delay(1000);
    eff.intakeToggle();
    drive.faceToPoint({-1_tile, 1_tile}, true);
    drive.goBackward(1.414_tile);
    eff.toggleClamp(); //clamp on
    eff.intakeToggle(); //turn on, put rings on mogo
    drive.faceToPoint({-1_tile, 1_tile}, true);
    drive.goForward(1.414_tile);
    drive.faceToPoint({0_tile, -1_tile}, true);
    drive.goForward(1_tile);
    drive.faceToPoint({2_tile, 0_tile}, true);
    drive.goForward(1.5_tile);
    drive.faceToPoint({-0.5_tile, 1_tile}, true); // weird
    drive.goBackward(1.12_tile);
    eff.toggleClamp(); //clamp off, mogo in corner
    eff.intakeToggle(); //intake off
    drive.faceToPoint({0_tile, 1_tile}, true);
    drive.goForward(5_tile); //slam mogo in corner
}