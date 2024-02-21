#include "effectors.h"
#include "parameters.h"
#include "controller.h"
#include "drive.h"

// WINGS
void Effectors::wingsToggle () {
    wingsActive = !wingsActive;
    wingsPistonLeft.set_value(wingsActive); // there's a get value here in piston
    wingsPistonRight.set_value(wingsActive); // there's a get value here in piston
}

// toggle four bar
void Effectors::toggleFourBar () {
    forBarActive = !forBarActive;
    fourBar.set_value(forBarActive);
}

// INTAKE
void Effectors::intakeToggle (bool reverse) {
    float reverseFactor = 1;
    if (intakeActive == IntakeState::INTAKE && reverse) {
        reverseFactor = -1; 
        intakeMotor.move_velocity(-600 * reverseFactor);
        intakeActive = IntakeState::OUTTAKE;
    } 
    else if (intakeActive == IntakeState::OUTTAKE && !reverse) {
        reverseFactor = 1;
        intakeMotor.move_velocity(-600 * reverseFactor);
        intakeActive = IntakeState::INTAKE;
    }
    else if (intakeActive == IntakeState::INACTIVE) {
        reverseFactor = reverse ? -1 : 1; 
        intakeMotor.move_velocity(-600 * reverseFactor);
        intakeActive = reverse ? IntakeState::OUTTAKE : IntakeState::INTAKE;
    }
    else if ((intakeActive == IntakeState::INTAKE && !reverse) || 
             (intakeActive == IntakeState::OUTTAKE && reverse))
    {
        intakeMotor.move_velocity(0);
        intakeActive = IntakeState::INACTIVE;
    }
}

void Effectors::setIntake (bool isReverse, bool isOff) {
    float powOne = (isReverse ? 1 : -1) * !isOff * 12000;
    float powTwo = (isReverse ? -1 : 1) * !isOff * 12000;
    intakeMotor.move_voltage(powOne);
}

bool Effectors::runSlapperSkill () {
    // assumes that the slapper is at the end position... at the last tooth gear
    eff.slapper.move_voltage(12000);
    eff.smallerSlapper.move_voltage(-12000);

    // 53600 too long 
    while (true) {
        pros::delay(30);
        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_R1)) {
            eff.slapper.move_voltage(0);
            eff.smallerSlapper.move_voltage(0);
            return false;
        }
    }

    eff.slapper.move_velocity(0);
    eff.smallerSlapper.move_velocity(0);
    eff.rotSensorShooter.set_position(0);
    return true;
}

