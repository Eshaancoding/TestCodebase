#ifndef EFFECTORS_H
#define EFFECTORS_H
#include "Console.h"
#include "parameters.h"
#include "main.h"
#include "pros/adi.hpp"

enum IntakeState {
    INTAKE,
    OUTTAKE,
    INACTIVE
};

// I could make this a namespace idk why im making it a class
class Effectors {
public:
    pros::Motor cata;
    pros::Motor intakeMotor;
    pros::Rotation rotSensor;

    pros::ADIDigitalOut piston;
    pros::ADIDigitalOut ptoPiston;
    bool wingsActive;
    IntakeState intakeActive;

    Effectors () : 
        cata(2, pros::E_MOTOR_GEAR_RED),
        intakeMotor(12, pros::E_MOTOR_GEAR_GREEN),    
        piston('A'),
        ptoPiston('B'),
        rotSensor(15),
        wingsActive(false),
        intakeActive(INACTIVE)
    { 
        rotSensor.set_position(0); 
    };
    ~Effectors() = default;

    // puncher
    void punch ();

    // wings
    void wingsToggle ();

    // intake
    void intakeToggle (bool reverse=false);
    void setIntake (bool isReverse=false, bool isOff=false); // SIMPLER version of intake; use this for auton

    // pto
    void setPTO (bool state);
    
    // raise the entire assembly
    void assemblyUp ();
    void assemblyDown ();

};

#endif