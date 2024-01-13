#include "effectors.h"
#include "parameters.h"
#include "drive.h"

// WINGS
void Effectors::wingsToggle () {
    wingsActive = !wingsActive;
    piston.set_value(wingsActive); // there's a get value here in piston
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

// PTO
void Effectors::setPTO (bool state) {
    ptoPiston.set_value(state);
    if (state == true) {
        leftPTOMotor.setBrakeMode(AbstractMotor::brakeMode::brake);
        rightPTOMotor.setBrakeMode(AbstractMotor::brakeMode::brake);
    } else {
        leftPTOMotor.setBrakeMode(AbstractMotor::brakeMode::coast);
        rightPTOMotor.setBrakeMode(AbstractMotor::brakeMode::coast);
    }
}

void Effectors::assemblyUp () {
    while (true) {
        // leftPTOMotor.moveVelocity(-600);
        // rightPTOMotor.moveVelocity(-600);
        leftPTOMotor.moveVoltage(-12000);
        rightPTOMotor.moveVoltage(-12000);

        if (rotSensorFB.get_position() < 8000) {
            Console::printBrain(6, "DONE");
            break;
        }
        pros::delay(200);
    }
    leftPTOMotor.moveVelocity(0);
    rightPTOMotor.moveVelocity(0);
}

void Effectors::assemblyDown () {
    while (true) {
        leftPTOMotor.moveVelocity(300);
        rightPTOMotor.moveVelocity(300);

        if (rotSensorFB.get_position() > 30000) break;
        pros::delay(200);
    }
    leftPTOMotor.moveVelocity(0);
    rightPTOMotor.moveVelocity(0);
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
        Console::printBrain(2, val, "val:");
        
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
    double prevRotSensorVal = 0;
    slapper.move_velocity(-100);
    setIntake();
    pros::delay(300);
    setIntake(false, true);
    while (true) {
        pros::delay(100);
        double currentRotSensor = rotSensor.get_position();
        Console::printBrain(4, abs(currentRotSensor - prevRotSensorVal));
        if (abs(currentRotSensor - prevRotSensorVal) < 850) break;
        prevRotSensorVal = currentRotSensor;
    }
    slapper.move_velocity(0);
    rotSensor.set_position(0);
}

void Effectors::lock () {
    lockEnabled = !lockEnabled;
    endGame.set_value(lockEnabled);
}

void Effectors::togglePTO () {
    if (isPTOEnabled) {
        eff.assemblyDown();
        eff.setPTO(false);
    } else {
        // drive.moveArcade(-0.1, 0);
        // pros::delay(100);
        eff.setPTO(true);
        // pros::delay(500);
        pros::delay(300);
        // drive.moveArcade(0, 0);
        eff.assemblyUp();       
    }

    isPTOEnabled = !isPTOEnabled;
}

bool Effectors::returnPTOState () {
    return isPTOEnabled;
}