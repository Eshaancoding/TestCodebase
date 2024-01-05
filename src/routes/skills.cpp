#include "routes.h"
#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::skills () {
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    // for (int i = 0; i < 43; i++) {
    //     eff.cataOne.move_velocity(100);
    //     eff.cataTwo.move_velocity(-100);
    //     pros::delay(300);
    //     // reset slapper
    //     eff.state = CataState::RESETTING;
    //     while (true) {
    //         eff.resetCata();
    //         if (eff.state == CataState::SHOOTING) { 
    //             break;
    //         }
    //         pros::delay(20);
    //     }
    //     // delay
    //     pros::delay(200);
    // }

    OdomCustom::setPos(0_in, 0_in, nullopt);
    drive.faceToPoint({0_in, -10_tile}, true, {{0, 0.7}});
    drive.goBackward(0.5_tile);
    drive.turnLeft(90_deg);
    drive.goBackward(5_tile);
    drive.turnRight(90_deg);
    drive.goBackward(3_tile);
    drive.turnRight(45_deg);
    drive.goBackward(1.41_tile);
    drive.turnRight(45_deg);

    // slam that shit
    drive.moveArcade(-1, 0);
    pros::delay(800); 
    drive.moveArcade(0, 0);

    drive.goForward(0.5_tile);
    drive.turnLeft(90_deg);
    drive.goForward(2_tile);
    drive.turnLeft(90_deg); 
    
    drive.goForward(2_tile);
    drive.turnRight(90_deg);

    drive.moveArcade(-1, 0);
    pros::delay(2000); 
    drive.moveArcade(0, 0);
}