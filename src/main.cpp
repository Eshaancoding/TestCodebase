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
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    
    eff.rotSensorShooter.set_position(0);
    // drive.goForward(2_tile);
    // drive.turnRight(135_deg);
    // Routes::skills();
    // Routes::qualOffensive();
    
    auto state = waitForValidState();     
    if (state.status == AutonSelector::SKILL)
        Routes::skills();
    else if (state.elimQualState == AutonSelector::ElimQualState::ELIM && state.offDefState == AutonSelector::OffDefState::DEFENSIVE) 
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
    bool isShooting = false;    
    bool isPTOEnabled = false;
    bool isIntaking = false;
    Control::printController(0, "Forward    ");

    // ================== COAST ================== 
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);

    eff.rotSensorShooter.set_position(0);

    while (true) {
        // ======================== Arcade ======================== 
        double heading =  Control::getAnalog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        double distance = Control::getAnalog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        // distance *= isReversed ? -1 : 1;

        // ======================== Tank ======================== 
        // double left = Control::getAnalog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        // double right = Control::getAnalog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        drive.moveArcade(distance, heading);

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_R1))
            isShooting = !isShooting;

        if (isShooting) {
            isShooting = eff.runSlapperSkill();
        }

        // ======================== Other Controls ======================== 
        // macro for toggling raising or lowering
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_L1)) 
            eff.wingsToggle();

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_R2)) {
            eff.toggleFourBar();
        }

        // toggle intake
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_L2)) {
            isIntaking = !isIntaking;
            eff.setIntake(false, isIntaking);
        }

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_UP)) {
            Routes::skills();
        }
        double rot_sensor_val = eff.rotSensorShooter.get_position();
        Console::printBrain(7, "Rot sensor shoot: %f", rot_sensor_val);

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            // run unti goes up
            // run up
            eff.rotSensorShooter.set_position(0);
            eff.slapper.move_voltage(12000*0.5);
            eff.smallerSlapper.move_velocity(-100*0.5);
            int count = 0;
            while (true) {  
                if (rot_sensor_val > 200 && count > 0) break;
                if (rot_sensor_val < -6000 && count == 0) count++;

                pros::delay(5);
                rot_sensor_val = eff.rotSensorShooter.get_position();
                Console::printBrain(7, "Rot sensor shoot: %f", rot_sensor_val);
            }
            eff.slapper.move_velocity(0);
            eff.smallerSlapper.move_velocity(0);
        }

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            eff.slapper.move_voltage(12000);
            eff.smallerSlapper.move_velocity(-100);
        } else {
            eff.slapper.move_voltage(0);
            eff.smallerSlapper.move_velocity(0);
        }

        // run it at end of macro
        // during auton (match) --> just spin a lil


        // // actual slapper
        // if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_R1))
        //     eff.toggleShootingState();
        // eff.stepShootMotor();

        pros::delay(10);

        Console::printBrain(0, OdomCustom::getPos(), "Get pos: ");
    }
}

// R2: macro to go up and PTO and shit. Make sure you go back down.
// L1: wings
// L2: move intake (no outtake)
// R1: Shooting (adi wants some fancy shit)