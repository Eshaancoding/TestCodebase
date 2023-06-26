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
    pros::ADIDigitalOut piston;
    pros::ADIDigitalOut expOne;
    pros::ADIDigitalOut expTwo;

public:
    bool shouldReset;
    Effectors () : 
        cataMotor(CATA_MOTOR), cataMotorTwo(CATA_MOTOR_TWO), intakeMotor(INTAKE_MOTOR), intakeMotorTwo(INTAKE_MOTOR_TWO), limitSwitch(LIMITSWITCH), piston(PISTON_ENABLE), expOne(EXPANSIONONE), expTwo(EXPANSIONTWO), shouldReset(true)
    {cataMotor.setBrakeMode(AbstractMotor::brakeMode::hold); cataMotorTwo.setBrakeMode(AbstractMotor::brakeMode::hold); };

    void reset ();

    ~Effectors () {expOne.set_value(true); expTwo.set_value(true);}

    void intake (std::int16_t power=127);
    void outtake (std::int16_t power=127);
    void stopIntake ();
    void stepCataReset ();
    void shoot ();

    void expand (bool one=true);

    void enablePiston ();
    void disablePiston ();

    void delay (QTime time);
};

#endif