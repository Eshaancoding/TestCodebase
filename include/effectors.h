#ifndef EFFECTORS_H
#define EFFECTORS_H

#include "Console.h"
#include "parameters.h"
#include "main.h"
#include "pros/adi.hpp"

// I could make this a namespace idk why im making it a class
class Effectors {
private:
    Motor cataMotor; 
    Motor cataMotorTwo;
    Motor intakeMotor;
    Motor intakeMotorTwo;

    pros::ADIDigitalIn limitSwitch;

    bool shouldReset;
public:
    Effectors () : 
        cataMotor(CATA_MOTOR), cataMotorTwo(CATA_MOTOR_TWO), intakeMotor(INTAKE_MOTOR), intakeMotorTwo(INTAKE_MOTOR_TWO), limitSwitch(LIMITSWITCH), shouldReset(true)
    {cataMotor.setBrakeMode(AbstractMotor::brakeMode::hold); cataMotorTwo.setBrakeMode(AbstractMotor::brakeMode::hold);};

    void intake (std::int16_t power=127);
    void outtake (std::int16_t power=127);
    void stopIntake ();
    void stepCataReset ();
    void shoot ();

    void delay (QTime time);
};

#endif