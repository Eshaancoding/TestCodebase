#include "effectors.h"
#include "Console.h"
#include "parameters.h"
#include "controller.h"
#include "drive.h"
#include "pros/optical.hpp"
#include <atomic>
#include <cstdarg>

// initailize all static variables
pros::Motor Effectors::intakeMotor (20);
pros::Optical Effectors::colorSensor (15);
std::atomic<IntakeState> Effectors::intakeActive = IntakeState::INACTIVE;
Color Effectors::colorState = Color::noColor;
std::atomic<bool> Effectors::isBlue = false;

// INTAKE
void Effectors::toggleIntakeState (IntakeState ia, bool isConveyor) {
    // outtaking, and we press the outtake button, disable
    // intaking, and we press the intake button, disable
    // disable, and press button,sdfsdfsdf then it won't satisfy this condition
    if (this->intakeActive == ia) {
        this->intakeActive = IntakeState::INACTIVE;
    } else {
        this->intakeActive = ia;
    }
}

void Effectors::intake () { 
    while (true) {
        IntakeState state = intakeActive.load();
        if (state == IntakeState::INTAKE) {
            // once it detects blue, stop conveyor after certain amount of encoder turns so it is at the top of arm
            // pros::c::optical_rgb_s_t rgbVal = colorSensor.get_rgb();
            // double encCount = intakeMotor.get_position();
            
            // if (!isBlue.load() && colorState == Color::noColor && rgbVal.red >= 200 && rgbVal.green <= 30 && rgbVal.blue <= 30){
            //     intakeMotor.set_zero_position(0);
            //     colorState = Color::red;
            // } else if (!isBlue.load() && colorState == Color::red && encCount >= 360){
            //     intakeMotor.move_voltage(0);
            //     pros::delay(500);
            //     intakeMotor.move_voltage(300);
            //     colorState = Color::noColor;
            // } else if (isBlue.load() && colorState == Color::noColor && rgbVal.red <= 30 && rgbVal.green <= 30 && rgbVal.blue >= 200){
            //     intakeMotor.set_zero_position(0);
            //     colorState = Color::blue;
            // } else if (isBlue.load() && colorState == Color::blue && encCount >= 360){
            //     intakeMotor.move_voltage(0);
            //     colorState = Color::noColor;
            //     pros::delay(500);
            //     intakeMotor.move_voltage(300);
            // }
            colorState = Color::noColor;
            intakeMotor.move_velocity(-300);
        } else if (state == IntakeState::OUTTAKE) {
            colorState = Color::noColor;
            intakeMotor.move_velocity(300);
        } else if (state == IntakeState::INACTIVE) {
            colorState = Color::noColor;
            intakeMotor.move_velocity(0);
        }

        pros::delay(50);
    }
}

void Effectors::setIntake (bool isReverse, bool isOff) {
    if (isOff)          intakeActive = IntakeState::INACTIVE;
    else if (isReverse) intakeActive = IntakeState::OUTTAKE;
    else                intakeActive = IntakeState::INTAKE;
}

void Effectors::setIntake (IntakeState state) {
    intakeActive = state;
}

void Effectors::toggleClamp(){
    isClamped = !isClamped;
    clampPiston.set_value(isClamped);
    // clampPistonRight.set_value(isClamped);
}

void Effectors::raiseArm () {
    armLeft.move_voltage(8000);
    armRight.move_voltage(-8000);
}

void Effectors::lowerArm () {
    armLeft.move_voltage(-8000);
    armRight.move_voltage(8000);
}

void Effectors::stopArm () {
    armLeft.move_velocity(0);
    armRight.move_velocity(0);
}

void Effectors::toggleBoinker () {
    boinkerActive = !boinkerActive;
    boinkerPiston.set_value(boinkerActive);
}


// fancy arm things
// press button -> arm turns a lil bit so conveyor can slide donut into it -> press button again -> 
// arm slams almost 180 to get donut onto wall stake

void Effectors::changeState () {
    if (this->currentState == State::IDLE) {
        this->currentState = State::isRaising;
    } else if (this->currentState == State::isRaising) {
        this->currentState = State::hasDonut;
    } else {
        this->currentState = State::IDLE;
    }
}

void Effectors::stepArm () {
    // there's no while true loop
    const double loadingAngle = 23; 
    const double dumpAngle = 120; 
    const double idleAngle = 2;

    const double initRotSensor = 9342;

    double targetAngle = this->currentState == State::isRaising ? loadingAngle : 
                         this->currentState == State::hasDonut ? dumpAngle :
                         idleAngle; // if idle

    double angle = ((double)rotationSensor.get_angle() - initRotSensor) / 100;

    double error = (angle - targetAngle)*3.1415926/180;
    double p = 70;

    armLeft.move_velocity(p * error);
    armRight.move_velocity(-p * error);
    Console::printBrain(8, "power: %f", p * error);
}