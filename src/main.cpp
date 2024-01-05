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
*************************************************************
Hi adi if you want an intro to the codebase,
you could head up to the README I documented some stuff
*************************************************************
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
    AutonSelector::init();

    leftPTOMotor.setGearing(AbstractMotor::gearset::blue);
    leftMotorGroup.setGearing(AbstractMotor::gearset::blue);
    rightMotorGroup.setGearing(AbstractMotor::gearset::blue);
    rightPTOMotor.setGearing(AbstractMotor::gearset::blue);

    leftPTOMotor.setBrakeMode(AbstractMotor::brakeMode::coast);
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightPTOMotor.setBrakeMode(AbstractMotor::brakeMode::coast);

    drive.resetToleranceParams();
    OdomCustom::init(); 
    Task task (OdomCustom::MainLoop);

}

// Autonomous Mode
void autonomous() {
    auto state = waitForValidState();
    if (state.side == AutonSelector::SideState::LEFT && state.risky == AutonSelector::RiskyState::RISKY) Routes::leftRisky();
    else if (state.side == AutonSelector::SideState::LEFT && state.risky == AutonSelector::RiskyState::SAFE) Routes::left();
    else if (state.side == AutonSelector::SideState::RIGHT && state.risky == AutonSelector::RiskyState::SAFE) Routes::right();
    else if (state.status == AutonSelector::TEST) Routes::skills();
};

// you disabled the factor map thing

void opcontrol() {
    bool isPTOEnabled = false;
    bool isIntaking = false;
    Control::printController(0, "Forward    ");

    // ================== COAST ================== 
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);

    while (true) {
        // ======================== Arcade ======================== 
        // double heading =  Control::getAnalog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        // double distance = Control::getAnalog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        // distance *= isReversed ? -1 : 1;

        // ======================== Tank ======================== 
        double left = Control::getAnalog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        double right = Control::getAnalog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        drive.moveTank(left, right);

        // ======================== Other Controls ======================== 
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_R2)) {
            if (isPTOEnabled) {
                eff.assemblyDown();
                eff.setPTO(false);
            } else {
                eff.setPTO(true);
                eff.assemblyUp();
            }
        }

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_L1)) eff.wingsToggle();
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_L2)) {
            isIntaking = !isIntaking;
            eff.setIntake(false, isIntaking);
        }

        // if (Control::getButtonPressed())

        pros::delay(10);
    }
}

// R2: macro to go up and PTO and shit. Make sure you go back down.
// L1: wings
// L2: move intake (no outtake)

// R1: Shooting (adi wants some fancy shit)
