#include "main.h"
#include "odom/Math.h"
#include "AutonSelector.h"
#include "Console.h"
#include "parameters.h"
#include "effectors.h"
#include "drive.h"
#include "controller.h"
#include "odom/OdomCustom.h"
#include "pros/misc.h"
#include "routes.h"

void disabled() {}
void competition_initialize() {}

/*

Hi adi if you want an intro to the codebase,
you could head up to the README I documented some stuff

*/

// Auton Selector wait state function (helper for autonomous and opcontrol)
AutonSelector::State waitForValidState () {
    AutonSelector::State state;
    
    // constantly check state change
    while (true) { 
        auto stateCheck = AutonSelector::getState();             
        auto isCalibrating = OdomCustom::isCalibrating();
 
        if (stateCheck.status == AutonSelector::TEST && !isCalibrating) {
            state = stateCheck;
            break;
        }
        else if (stateCheck.status == AutonSelector::ROUTE && !isCalibrating) {
            state = stateCheck;
            break;
        }

        pros::delay(200); // doesn't have to check too often :)
    }
    return state;
}

// When robot initializes. 
void initialize() {
    leftMotorGroup.setGearing(AbstractMotor::gearset::blue);
    rightMotorGroup.setGearing(AbstractMotor::gearset::blue);
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    drive.resetToleranceParams();
    OdomCustom::init(); 
    Task task (OdomCustom::MainLoop);
}

// Autonomous Mode
void autonomous() {
    Routes::leftRisky();
};

// you disabled the factor map thing

void opcontrol() {
    bool isCoast = true;
    bool isReversed = false;
    Control::printController(0, "Forward    ");

    while (true) {
        // ======================== Arcade ======================== 
        double heading =  Control::getAnalog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        double distance = Control::getAnalog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        distance *= isReversed ? -1 : 1;

        // Robot turning to fast? Note that heading is from -1 to 1
        // heading *= 0.5; // 50% speed

        drive.moveArcade(distance, heading);

        // ======================== Tank ======================== 
        // double left = Control::getAnalog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        // double right = Control::getAnalog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        // drive.moveTank(left, right);

        // ======================== Other Controls ======================== 
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            isReversed = !isReversed;
            if (isReversed) Control::printController(0, "Reversed");
            else            Control::printController(0, "Forward    ");
        }

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            isCoast = !isCoast;
            if (isCoast) {
                leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
                rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
            } 
            else {
                leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
                rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
            }
        }
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_A))    eff.wingsToggle(); 
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_B))    eff.intakeToggle();
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_R2))   eff.shootCata();
        eff.resetCata();

        pros::delay(10);
    }
}