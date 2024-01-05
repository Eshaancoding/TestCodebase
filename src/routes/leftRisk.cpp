#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::leftRisky () {
    // OdomCustom::setPos(0_in, 0_in, 135_deg);
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);

    OdomCustom::setPos(0_in, 0_in, 135_deg);

    // ================= GO BACK TO RESET ================= 
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotorGroup.moveVelocity(300);
    leftMotorGroup.moveVelocity(0);
    pros::delay(400);
    rightMotorGroup.moveVelocity(0);
    leftMotorGroup.moveVelocity(0);
    pros::delay(200);

    // ================= GO FORWARD A LIL ================= 
    eff.wingsToggle();
    drive.goBackward(1_in);
    pros::delay(100);

    // ================= SPIN SUCH THAT IT GETS THE TRIBALL OUT ================= 
    drive.moveArcade(0, -400);
    pros::delay(800);
    drive.moveArcade(0, 0);
    eff.wingsToggle();
    pros::delay(300);

    // ================= SPIN SUCH THAT IT GETS THE TRIBALL OUT ================= 
    OdomCustom::setPos(0_in, 0_in);
    drive.faceToPoint({-10_tile, -10_tile}, true);

    // ================= GO TO POSITION ================= 
    drive.setToleranceParams(nullopt, nullopt, 1.5_s);
    drive.goBackward(16_in);
    drive.resetToleranceParams();
    drive.faceToPoint({-1_tile, -10_tile}, true);

    // ================= GO FORWARD ================= 
    // figure this out 

}

