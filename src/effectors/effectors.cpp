#include "effectors.h"
#include "Console.h"
#include "parameters.h"
#include "controller.h"
#include "drive.h"
#include "pros/motors.h"
#include "pros/optical.hpp"
#include <atomic>
#include <cstdarg>

// initailize all static variables
pros::Motor Effectors::intakeMotor (10, MOTOR_GEAR_BLUE);
pros::Optical Effectors::colorSensor (9);
std::atomic<IntakeState> Effectors::intakeActive = IntakeState::INACTIVE;
Color Effectors::colorState = Color::noColor;
std::atomic<bool> Effectors::isBlue = false; // by default we assume that we are blue
std::atomic<bool> Effectors::seeColor = true; // yes color sensor code

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

//colorState = Color::noColor;

void Effectors::intake () { 
    const int firstDelay = 10;    
    const int secondDelay = 200;    

    while (true) {
        IntakeState state = intakeActive.load();
        const bool is_blue = isBlue.load(); // ===== By default: false ======
        const bool see_color = seeColor.load(); // deafult true
        double hue = colorSensor.get_hue();
        double blue = colorSensor.get_rgb().blue;
        double red = colorSensor.get_rgb().red;
        double green = colorSensor.get_rgb().green;
        Console::printBrain(0, hue, "hue");
        Console::printBrain(1, red, "red");
        Console::printBrain(2, green, "green");
        Console::printBrain(3, blue, "blue");
        
        if (!see_color && state == IntakeState::INTAKE) {
            // once it detects blue, stop conveyor after certain amount of encoder turns so it is at the top of arm
            
            /*
            // First condition: we on red side; hue < 10 means detech red
            if (is_blue && hue < 10) { 
                pros::delay(firstDelay);
                intakeMotor.move_velocity(0);
                pros::delay(secondDelay);
                intakeMotor.move_velocity(600);
            }
            
            // First condition: we on blue side; hue > 120 means detech blue
            else if (!is_blue && hue > 120) {
                pros::delay(firstDelay);
                intakeMotor.move_velocity(0);
                pros::delay(secondDelay);
                intakeMotor.move_velocity(600);
            } 
            
            else {
                intakeMotor.move_velocity(600);
            }
            */
            intakeMotor.move_velocity(600);

        } else if (see_color && state == IntakeState::INTAKE){
            if (is_blue && hue < 10) { 
                pros::delay(firstDelay);
                intakeMotor.move_velocity(0);
                pros::delay(secondDelay);
                intakeMotor.move_velocity(600);
            }
            
            // First condition: we on blue side; hue > 120 means detech blue
            else if (!is_blue && hue > 120) {
                pros::delay(firstDelay);
                intakeMotor.move_velocity(0);
                pros::delay(secondDelay);
                intakeMotor.move_velocity(600);
            } 
            
            else {
                intakeMotor.move_velocity(600);
            }
        } else if (state == IntakeState::OUTTAKE) {
            intakeMotor.move_velocity(-600);
        } else if (state == IntakeState::INACTIVE) {
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