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
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::brake);

    drive.resetToleranceParams();
    eff.arm.set_zero_position(0);
    OdomCustom::init(); 

    Task task (OdomCustom::MainLoop); // multithreading
}

// Autonomous Mode
void autonomous() {
    leftMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotorGroup.setBrakeMode(AbstractMotor::brakeMode::coast);
    
    // drive.goForward(2_tile);
    // drive.turnRight(135_deg);
    // Routes::skills();
    // Routes::qualOffensive();

    AutonSelector::State state = AutonSelector::getState(); 

    if (state.status == AutonSelector::SKILL) {
        Routes::skills();
    }
    else if (state.offDefState == AutonSelector::OFFENSIVE) {
        Routes::mogoSideMatchBlue();
    } 
    else if (state.offDefState == AutonSelector::DEFENSIVE) {
        Routes::mogoSideMatchRed();
    }

    

    // if (state.status == AutonSelector::SKILL)
    //     Routes::new_skills();
    // else if (state.elimQualState == AutonSelector::ElimQualState::ELIM && state.offDefState == AutonSelector::OffDefState::DEFENSIVE) 
    //     Routes::sixBall();
    // else if (state.elimQualState == AutonSelector::ElimQualState::ELIM && state.offDefState == AutonSelector::OffDefState::OFFENSIVE) 
    //     Routes::qualDefensive();
    // else if (state.elimQualState == AutonSelector::ElimQualState::QUAL && state.offDefState == AutonSelector::OffDefState::DEFENSIVE) 
    //     Routes::qualDefensive();
    // else if (state.elimQualState == AutonSelector::ElimQualState::QUAL && state.offDefState == AutonSelector::OffDefState::OFFENSIVE) 
    //     Routes::qualOffensive();

    // drive.goForward(1_tile);
    // drive.turnRight(90_deg);
    // drive.goBackward(1_tile);
};

// you disabled the factor map thing

void opcontrol() {
    bool isShooting = false;    
    bool isPTOEnabled = false;
    bool isIntaking = false;
    bool isReverse = false;
    bool hasDonut = false;
    Control::printController(0, "Forward");

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

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_UP))
            eff.toggleBoinker();

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            isReverse = !isReverse;
            Control::printController(0, isReverse ? "Reverse" : "Forward");
        }

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_B)) {
            eff.changeState();
        }

        eff.stepArm();

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_L2))
            eff.setIntakeState(IntakeState::OUTTAKE);

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_L1))
            eff.setIntakeState(IntakeState::INTAKE);

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_X))
            eff.toggleClamp();           

        if (Control::getButtonPressed(pros::E_CONTROLLER_DIGITAL_R1))
            eff.raiseArm();

        else if (Control::getButtonPressed(pros::E_CONTROLLER_DIGITAL_R2))
            eff.lowerArm();
        else
            eff.stopArm();

        // eff.stepOuttake();

        pros::delay(10);
    }
};

// R2: macro to go up and PTO and shit. Make sure you go back down.
// L1: wings
// L2: move intake (no outtake)
// R1: Shooting (adi wants some fancy shit)

//

//drive forward, initialize 4 motors also pid
//go forwad 2 tiles with 4 motors using pid
//p2: update angle error correction
/*
void car(double distance){
    pros::Motor rightF; //initialize
    pros::Motor rightB;
    pros::Motor leftF;
    pros::Motor leftB;
    double motorDiameter = 5;
    rightF.set_zero_position(0); //reset encoder
    
    distance = (distance/motorDiameter)*360; //convert distance to degrees
    double error = distance - rightF.get_position(); //calculate error

    PID p = PID(0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
    PID h = PID(0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
    double factor = p.step(error); //get factor
    double heading = OdomCustom::angleGet();
    double hfactor = h.step(heading);
    while (error>0){
        rightF.move_velocity(200*factor);
        rightB.move_velocity(200*factor);
        leftF.move_velocity(200*factor);
        leftB.move_velocity(200*factor);
        while (heading > 0){
            rightF.move_velocity(hfactor*200);
            rightB.move_velocity(hfactor*200);
        }
        while (heading < 0){
            leftF.move_velocity(hfactor*200);
            leftB.move_velocity(hfactor*200);
        }
        error = distance - rightF.get_position(); //find new error
        factor = p.step(error); //get new factor
    }

//
}*/