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
 
        if (stateCheck.status == AutonSelector::SKILL && !isCalibrating) {
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
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    
    auto state = waitForValidState();     

    // if (state.elimQualState == AutonSelector::ElimQualState::ELIM) Console::printBrain(0, "Elim");
    // else if (state.elimQualState == AutonSelector::ElimQualState::QUAL) Console::printBrain(0, "Qual");
    
    // if (state.offDefState == AutonSelector::OFFENSIVE) Console::printBrain(1, "Offensive.");
    // else if (state.offDefState == AutonSelector::DEFENSIVE) Console::printBrain(1, "Defensive.");

    if (state.elimQualState == AutonSelector::ElimQualState::ELIM && state.offDefState == AutonSelector::OffDefState::DEFENSIVE) 
        Routes::elimDefensive();
    else if (state.elimQualState == AutonSelector::ElimQualState::ELIM && state.offDefState == AutonSelector::OffDefState::OFFENSIVE) 
        Routes::elimOffensive();
    else if (state.elimQualState == AutonSelector::ElimQualState::QUAL && state.offDefState == AutonSelector::OffDefState::DEFENSIVE) 
        Routes::qualDefensive();
    else if (state.elimQualState == AutonSelector::ElimQualState::QUAL && state.offDefState == AutonSelector::OffDefState::OFFENSIVE) 
        Routes::qualOffensive();
};

// you disabled the factor map thing

void opcontrol() {
    eff.resetShoot();
    bool isPTOEnabled = false;
    bool isIntaking = false;
    Control::printController(0, "Forward    ");


    // ================== COAST ================== 
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);

    while (true) {
        // ======================== Arcade ======================== 
        double heading =  Control::getAnalog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        double distance = Control::getAnalog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        // distance *= isReversed ? -1 : 1;

        // ======================== Tank ======================== 
        // double left = Control::getAnalog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        // double right = Control::getAnalog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        drive.moveTank(distance, heading);
        // drive.moveArcade(distance, heading);

        // ======================== Other Controls ======================== 
        // macro for toggling raising or lowering
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_R2)) {
            eff.togglePTO();
        }

        // wings toggle
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_L1)) 
            eff.wingsToggle();

        // toggle intake
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_L2)) {
            isIntaking = !isIntaking;
            eff.setIntake(false, isIntaking);
        }

        // slapper test
        // Console::printBrain(1, OdomCustom::distanceGet(), "Enc: ");
        // if (Control::getButtonPressed(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        //     eff.slapper.move_velocity(-100);
        // }
        // else {
        //     eff.slapper.move_velocity(0);
        // }

        // Lock
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_DOWN)) eff.lock();

        // actual slapper
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_R1))
            eff.toggleShootingState();
        eff.stepShootMotor();

        pros::delay(10);
    }
}

// R2: macro to go up and PTO and shit. Make sure you go back down.
// L1: wings
// L2: move intake (no outtake)

// R1: Shooting (adi wants some fancy shit)


//  
