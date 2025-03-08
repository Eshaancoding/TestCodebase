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
#include "pros/rtos.hpp"
#include "routes.h"
#include "lemlib/api.hpp" // IWYU pragma: keep

void disabled() {}
void competition_initialize() {}

/*
*************************************************************
Hi adi if you want an intro to the codebase,
you could head up to the README I documented some stuff
*************************************************************
*/

// NEEDS TUNING
lemlib::ControllerSettings linearController(
    0.068, //kp
    0, //ki
    0.038, //kd
    3, // anti windup
    0.5, // small error range (in)
    100, // samll error range timeout (ms)
    3, // large error range (in)
    500, // large error range timeout (ms)
    1 // max acceleration (slew)
);

lemlib::ControllerSettings angularController(
    0.292, //kp
    0, //ki
    0.049, //kd
    3, // anti windup
    0.51, // small error range (deg)
    100, // small error range timeout (ms)
    3, // large error rnage (deg)
    500, // large error range timeout (ms)
    1 // max accel (slew)
);

// drive controller settings
lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband uot of 127
                                     10, // min output where drivetrain will move out of 127
                                     1.109 // expo curve gain
                                    );

lemlib::ExpoDriveCurve steerCurve(3,
                                  10,
                                  1.019
                                );

// chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttelCurve, &steerCurve);


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

    chassis.calibrate(); // calibrate sensors
 
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

    Routes::AWPRed();

	// drive.turnRight(200_deg);

    // OdomArc::setPos(0_in, 0_in, 0_deg);
    // drive.goForward(3_tile);
    // drive.goBackward(3_tile);

    // AutonSelector::State state = waitForValidState(); 

    // if (state.status == AutonSelector::SKILL) {
    //     Routes::skills();
    //     //Console::printBrain(1,"Distance: ",leftMotorGroup.getPosition())
    // }
    // else {
    //     if (state.offDefState == AutonSelector::BLUE) {
    //         eff.isBlue = true;
    //     } 
    //     else if (state.offDefState == AutonSelector::RED) {
    //         eff.isBlue = false;
    //     } 

    //     if (state.elimQualState == AutonSelector::QUAL) {
    //         Routes::ringSide(); 
    //     } 
    //     else if (state.elimQualState == AutonSelector::ELIM) {
    //         Routes::mogoSide();
    //     }
    // }
};

// you disabled the factor map thing

void opcontrol() {
    // Routes::mogoSideMatchBlue();
    // return;

    // eff.seeColor = false;

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
        //drive.moveArcade((isReverse ? -distance : distance), heading);
        chassis.arcade(distance, heading);


        // color
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_LEFT)){
            eff.seeColor = !eff.seeColor;
            if (eff.seeColor)
                Control::printController(0, "Color Sensor Activated");
            else
                Control::printController(0, "Color Sensor Deactivated");
        }

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_RIGHT))
            eff.toggleBoinker();

        // if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        //     isReverse = !isReverse;
        //     Control::printController(0, isReverse ? "Reverse" : "Forward");
        // }

        

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_L1)) {
            eff.arm_state = ArmState::PID_ARM;
            eff.changeState(); // lady brown
        }

        if (Control::getButtonPressed(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            eff.arm_state = ArmState::Raising_ARM;
        } 
        else if (Control::getButtonPressed(pros::E_CONTROLLER_DIGITAL_B)) {
            eff.arm_state = ArmState::Lowering_ARM; // this is reversed kinda
        }
        else {
            if (eff.arm_state != ArmState::PID_ARM) { // only do this after raising and lowering
                eff.arm_state = ArmState::IDLE_ARM; 
            }
        }

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