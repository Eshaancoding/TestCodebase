#ifndef EFFECTORS_H
#define EFFECTORS_H
#include "Console.h"
#include "parameters.h"
#include "main.h"
#include "pros/adi.hpp"

// I could make this a namespace idk why im making it a class
class Effectors {
public:
    pros::Motor arm;
    pros::Motor intakeMotor;
    pros::Motor conveyorMotor;

    pros::ADIDigitalOut clampPistonLeft;
    pros::ADIDigitalOut clampPistonRight;

    bool isClamped;
    bool intakeActive;

    Effectors () : 
        arm(3),
        intakeMotor(3),
        conveyorMotor(3),
        clampPistonLeft('A'),
        clampPistonRight('A'),
        isClamped(false),
        intakeActive(false)
    {
        arm.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);  //PRAC code
    };
    ~Effectors() = default;

    // intake
    void intakeToggle (bool reverse=false); //turn on convey
    void setIntake (bool isReverse=false, bool isOff=false); // SIMPLER version of intake; use this for auton

    //arm
    void toggleArm();  //PRAC code

    //clamp
    void toggleClamp();

};

#endif