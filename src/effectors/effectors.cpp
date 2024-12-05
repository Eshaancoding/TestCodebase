#include "effectors.h"
#include "parameters.h"
#include "controller.h"
#include "drive.h"
#include <cstdarg>

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
            rgbVal = colorSensor.get_rgb();
            double encCount = intakeMotor.get_position();
            
            if (!isBlue.load() && this->colorState == Color::noColor && rgbVal.red >= 200 && rgbVal.green <= 30 && rgbVal.blue <= 30){
                intakeMotor.set_zero_position(0);
                this->colorState = Color::red;
            } else if (!isBlue.load() && this->colorState == Color::red && encCount >= 360){
                intakeMotor.move_voltage(0);
                pros::delay(500);
                intakeMotor.move_voltage(300);
                this->colorState = Color::noColor;
            } else if (isBlue.load() && this->colorState == Color::noColor && rgbVal.red <= 30 && rgbVal.green <= 30 && rgbVal.blue >= 200){
                intakeMotor.set_zero_position(0);
                this->colorState = Color::blue;
            } else if (isBlue.load() && this->colorState == Color::blue && encCount >= 360){
                intakeMotor.move_voltage(0);
                this->colorState = Color::noColor;
                pros::delay(500);
                intakeMotor.move_voltage(300);
            }
        } else if (state == IntakeState::OUTTAKE) {
            this->colorState = Color::noColor;
            intakeMotor.move_voltage(-300);
        } else if (state == IntakeState::INACTIVE) {
            this->colorState = Color::noColor;
            intakeMotor.move_voltage(0);
        }

        pros::delay(50);
    }
}

void Effectors::setIntake (bool isReverse, bool isOff) {
    if (isOff)          intakeActive = IntakeState::INACTIVE;
    else if (isReverse) intakeActive = IntakeState::OUTTAKE;
    else                intakeActive = IntakeState::INTAKE;
}

void Effectors::toggleClamp(){
    isClamped = !isClamped;
    clampPistonLeft.set_value(isClamped);
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
    double angle = rotationSensor.get_angle();
    if (this->currentState == State::isRaising && angle < 30){
        armLeft.move_voltage(300);
        armRight.move_voltage(-300);
    } else if (this->currentState == State::hasDonut && angle >= 30){
        armLeft.move_voltage(300);
        armRight.move_voltage(-300);
    } else if (this->currentState == State::hasDonut && angle > 170){
        armLeft.move_voltage(0);
        armRight.move_voltage(0);
    } else if (this->currentState == State::IDLE && angle > 0) {
        armLeft.move_voltage(-300);
        armRight.move_voltage(300);
    } else {
        armLeft.move_voltage(0);
        armRight.move_voltage(0);
    }
}