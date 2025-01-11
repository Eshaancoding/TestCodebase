#include "main.h"
#include "odom/Math.h"
#include "AutonSelector.h"
#include "Console.h"
#include "parameters.h"
#include "effectors.h"
#include "drive.h"
#include "controller.h"
#include "odom/OdomCustom.h"
#include "odom/OdomArc.h"
#include "pros/adi.hpp"
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
        auto isCalibrating = OdomArc::isCalibrating();
 
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
    // AutonSelector::init();

    leftMotorGroup.setGearing(AbstractMotor::gearset::blue);
    rightMotorGroup.setGearing(AbstractMotor::gearset::blue);
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);

    drive.resetToleranceParams();
    //eff.armLeft.set_zero_position(0);
    eff.armRight.set_zero_position(0);
    
    // make sure to change all instances to OdomArc asw (instead of OdomCustom)
    OdomArc::init(); 
    Task task (OdomArc::MainLoop); 

    Task colorCheck (Effectors::intake);
}

// Autonomous Mode
void autonomous() {
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    
    eff.seeColor = false;

    Routes::skills();
    // drive.turnRight(90_deg);
    // AutonSelector::State state = waitForValidState(); 

    // if (state.status == AutonSelector::SKILL) {
    //     Routes::skills();
    // }
    // else if (state.offDefState == AutonSelector::BLUE) {
    //     eff.isBlue = true;
    //     Routes::mogoSide();
    // } 
    // else if (state.offDefState == AutonSelector::RED) {
    //     eff.isBlue = false;
    //     Routes::mogoSideMatchRedElim();
    // }  

};

// you disabled the factor map thing

void opcontrol() {
    // Routes::mogoSideMatchBlue();
    // return;

    eff.seeColor = false;

    bool isShooting = false;    
    bool isPTOEnabled = false;
    bool isIntaking = false;
    bool isReverse = false;
    bool hasDonut = false;

    // ================== COAST ================== 
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);

    while (true) {
        // ======================== Arcade ======================== 
        double heading =  Control::getAnalog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        double distance = Control::getAnalog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

        // ======================== Tank ======================== 
        // double left = Control::getAnalog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        // double right = Control::getAnalog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        drive.moveArcade((isReverse ? -distance : distance) * 0.8, heading * 0.8);


        // color
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_LEFT)){
            eff.seeColor = !eff.seeColor;
            if (eff.seeColor)
                Control::printController(0, "Color Sensor Activated");
            else
                Control::printController(0, "Color Sensor Deactivated");
        }

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_UP))
            eff.toggleBoinker();

        // if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        //     isReverse = !isReverse;
        //     Control::printController(0, isReverse ? "Reverse" : "Forward");
        // }

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_L1))
            eff.changeState(); // lady brown
        eff.stepArm();

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_R1)){
            eff.toggleIntakeState(IntakeState::INTAKE);
        } 

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_R2)){
            eff.toggleIntakeState(IntakeState::OUTTAKE);
        }

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_L2))
            eff.toggleClamp();           

        // eff.stepOuttake();

        pros::delay(10);
    }
};