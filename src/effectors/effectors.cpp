#include "effectors.h"
#include "parameters.h"
#include "drive.h"

// WINGS
void Effectors::wingsToggle () {
    wingsActive = !wingsActive;
    wingsPiston.set_value(wingsActive); // there's a get value here in piston
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

void Effectors::toggleShootingState () {
    if (shootState == ShootState::SHOOTING) {
        shootState = ShootState::STOPPING;
    }
    else if (shootState == ShootState::DORMANT || shootState == ShootState::STOPPING) {
        shootState = ShootState::SHOOTING;
    }
}

void Effectors::stepShootMotor () {
    if (shootState == ShootState::SHOOTING) {
        slapper.move_velocity(-100);
    }
    else if (shootState == ShootState::DORMANT) {
        slapper.move_velocity(0);
    }
    else if (shootState == ShootState::STOPPING) {
        int val = rotSensor.get_position()/100;
        
        if (abs(val) > 5) {
            shootState = ShootState::STOPPING;
            slapper.move_velocity(-100);
        } else {
            shootState = ShootState::DORMANT;
            slapper.move_velocity(0);
        }
    }
}

void Effectors::resetShoot() {
    // reset slapper
    rotSensor.set_position(0);
 
    // eff.slapper.move_velocity(100);
    // eff.smallerSlapper.move_velocity(-100);

    // while (rotSensor.get_position() < 8600) {
    //     pros::delay(50);
    // }

    // slapper.move_velocity(0);
    // smallerSlapper.move_velocity(0);

}

