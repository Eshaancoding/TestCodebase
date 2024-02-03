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
    pros::Motor smallerSlapper;

    pros::Motor intakeMotor;
    
    pros::Rotation rotSensor;
    pros::Rotation rotSensorShooter;

    pros::ADIDigitalOut wingsPiston;
    pros::ADIDigitalOut fourBar;
    
    bool forBarActive;
    bool wingsActive;
    IntakeState intakeActive;
    ShootState shootState;

    bool lockEnabled;

    Effectors () : 
        slapper(13, pros::E_MOTOR_GEAR_GREEN),
        smallerSlapper(14, pros::E_MOTOR_GEAR_GREEN),
        intakeMotor(5, pros::E_MOTOR_GEAR_GREEN),    
        wingsPiston('B'),
        fourBar('A'),
        rotSensor(18),
        rotSensorShooter(11),
        wingsActive(false),
        forBarActive(false),
        shootState(DORMANT),
        intakeActive(INACTIVE),
        lockEnabled(false)
    { 
        slapper.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        smallerSlapper.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        eff.rotSensorShooter.set_position(0);
    };
    ~Effectors() = default;

    // wings
    void wingsToggle ();

    // intake
    void intakeToggle (bool reverse=false);
    void setIntake (bool isReverse=false, bool isOff=false); // SIMPLER version of intake; use this for auton

    // do four bar
    void toggleFourBar ();

    // lock
    void lock ();

    // skills run
    bool runSlapperSkill ();
};

#endif