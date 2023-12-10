#include "routes.h"

void Routes::skills () {
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    while (true) {
        eff.cataOne.move_velocity(100);
        eff.cataTwo.move_velocity(-100);
        pros::delay(300);
        // reset cata
        eff.state = CataState::RESETTING;
        while (true) {
            eff.resetCata();
            if (eff.state == CataState::SHOOTING) { 
                break;
            }
            pros::delay(20);
        }
        pros::delay(200);
    }
        
}