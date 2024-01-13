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
    pros::Rotation rotSensorFB;

    pros::ADIDigitalOut piston;
    pros::ADIDigitalOut ptoPiston;
    pros::ADIDigitalOut endGame;
    bool wingsActive;
    IntakeState intakeActive;
    ShootState shootState;

    bool isPTOEnabled;

    bool lockEnabled;

    Effectors () : 
        slapper(13, pros::E_MOTOR_GEAR_RED),
        intakeMotor(19, pros::E_MOTOR_GEAR_GREEN),    
        piston('A'),
        ptoPiston('B'),
        endGame('C'),
        rotSensor(18),
        rotSensorFB(9),
        wingsActive(false),
        shootState(DORMANT),
        intakeActive(INACTIVE),
        isPTOEnabled(false),
        lockEnabled(false)
    { 
        slapper.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    };
    ~Effectors() = default;

    // wings
    void wingsToggle ();

    // intake
    void intakeToggle (bool reverse=false);
    void setIntake (bool isReverse=false, bool isOff=false); // SIMPLER version of intake; use this for auton

    // pto
    void setPTO (bool state);
    void togglePTO ();
    bool returnPTOState ();
    
    // raise the entire assembly
    void assemblyUp ();
    void assemblyDown ();


    // shooting with puncher
    void resetShoot ();
    void toggleShootingState ();
    void stepShootMotor ();

    // lock
    void lock ();

};

#endif