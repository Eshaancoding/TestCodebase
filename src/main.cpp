#include "main.h"
#include "odom/Math.h"
#include "AutonSelector.h"
#include "Console.h"
#include "parameters.h"
#include "effectors.h"
#include "drive.h"
#include "controller.h"
#include "pros/misc.h"

void disabled() {}
void competition_initialize() {}

// Auton Selector wait state function (helper for autonomous and opcontrol)
AutonSelector::State waitForValidState () {
    AutonSelector::State state;
    
    // constantly check state change
    while (true) { 
        auto stateCheck = AutonSelector::getState();             
 
        if (stateCheck.status == AutonSelector::TEST) {
            state = stateCheck;
            break;
        }
        else if (stateCheck.status == AutonSelector::ROUTE) {
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
}

// Autonomous Mode
void autonomous() {
    auto state = waitForValidState();    

    effectors.enablePiston();
};

// Operation control (driver)
void opcontrol() {
    
    bool isEnabled = false;
    effectors.disablePiston();

    while (true) {
        double analogLeft = Control::getAnalog(E_CONTROLLER_ANALOG_LEFT_Y);
        double analogRight = Control::getAnalog(E_CONTROLLER_ANALOG_RIGHT_Y);

        double l = odometery.getLeftRevs();
        double r = odometery.getRightRevs();
        Console::printBrain(1, "left %.3f right %.3f", l, r);

        drive.moveTank(analogLeft, analogRight);

        if (Control::getButtonPressed(E_CONTROLLER_DIGITAL_L1)) {
            effectors.shoot();
        }

        if (Control::getButtonPressed(E_CONTROLLER_DIGITAL_R1)) {
            effectors.intake(127);
        }
        else if (Control::getButtonPressed(E_CONTROLLER_DIGITAL_R2)) {
            effectors.outtake(127);
        }
        else {
            effectors.stopIntake();
        }

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_UP)) {
            isEnabled = !isEnabled;
            if (isEnabled) {
                Control::printController(0, "Piston Enabled  ");
                effectors.enablePiston();
            } else {
                Control::printController(0, "Piston Disabled");
                effectors.disablePiston();
            }
        }

        effectors.stepCataReset();

        Console::printBrain(0, odometery.getPos(), "Pos");
        
        pros::delay(10);
    }
}