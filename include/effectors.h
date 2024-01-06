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

enum ShootState {
    STOPPING,
    SHOOTING,
    DORMANT
};

// I could make this a namespace idk why im making it a class
class Effectors {
public:
    pros::Motor slapper;
    pros::Motor intakeMotor;
    
    pros::Rotation rotSensor;

    pros::ADIDigitalOut piston;
    pros::ADIDigitalOut ptoPiston;
    bool wingsActive;
    IntakeState intakeActive;
    ShootState shootState;

    Effectors () : 
        slapper(12, pros::E_MOTOR_GEAR_RED),
        intakeMotor(19, pros::E_MOTOR_GEAR_GREEN),    
        piston('A'),
        ptoPiston('B'),
        rotSensor(17),
        wingsActive(false),
        shootState(DORMANT),
        intakeActive(INACTIVE)
    { 
        rotSensor.set_position(0); 
    };
    ~Effectors() = default;

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

    // shooting with puncher
    void toggleShootingState ();
    void stepShootMotor ();

};

#endif