#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::leftRisky () {
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);


    // ================== SHOOTS CATA ================== 
    while (true) {
        eff.resetCata();
        if (eff.state == CataState::SHOOTING) { 
            break;
        }
        pros::delay(20);
    }
     
    eff.cataOne.move_velocity(100);
    eff.cataTwo.move_velocity(-100);
    pros::delay(300); 
    eff.cataOne.move_velocity(0);
    eff.cataTwo.move_velocity(0);

    while (true) {
        eff.resetCata();
        if (eff.state == CataState::SHOOTING) { 
            break;
        }
        pros::delay(20);
    }
    // ================== DONE SHOOT CATA ================== 

    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
}
