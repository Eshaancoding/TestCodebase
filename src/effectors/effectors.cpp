#include "effectors.h"

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
    leftPTOMotor.moveVelocity(-400);
    rightPTOMotor.moveVelocity(400);
    pros::delay(300);
    leftPTOMotor.moveVelocity(0);
    rightPTOMotor.moveVelocity(0);
}

void Effectors::assemblyDown () {
    leftPTOMotor.moveVelocity(400);
    rightPTOMotor.moveVelocity(-400);
    pros::delay(300);
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
    pros::delay(400);
    while (true) {
        pros::delay(100);
        double currentRotSensor = rotSensor.get_position();
        Console::printBrain(4, abs(currentRotSensor - prevRotSensorVal));
        if (abs(currentRotSensor - prevRotSensorVal) < 1000) break;
        prevRotSensorVal = currentRotSensor;
    }
    slapper.move_velocity(0);
    rotSensor.set_position(0);
}