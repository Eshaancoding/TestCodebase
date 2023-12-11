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
    // ================== SHOOTS CATA ================== 
    while (true) {
        eff.resetCata();
        if (eff.state == CataState::SHOOTING) { 
            break;
        }
        pros::delay(20);
    }

    // ================= CURVE AND SHOOT ================= 
    leftMotorGroup.moveVelocity(100);
    rightMotorGroup.moveVelocity(-600);
    eff.cataOne.move_velocity(100);
    eff.cataTwo.move_velocity(-100);
    pros::delay(300); 
    eff.cataOne.move_voltage(0);
    eff.cataTwo.move_voltage(0);
    leftMotorGroup.moveVelocity(0);
    rightMotorGroup.moveVelocity(0);
    pros::delay(300);

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
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    double prevValue = eff.rotSensor.get_position();
    int i = 0;
    while (true) {
        pros::delay(100);
        drive.moveArcade(-0.4, 0);

        double currentValue = eff.rotSensor.get_position();
        Console::printBrain(5, currentValue - prevValue, "test");
        if (abs(currentValue - prevValue) > 10 && i > 10) {
            Console::printBrain(6, "broken");
            drive.moveArcade(0,0);
            break;
        }
        i += 1;

        prevValue = currentValue;
    }

}

