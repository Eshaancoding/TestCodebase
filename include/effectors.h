#ifndef EFFECTORS_H
#define EFFECTORS_H
#include "Console.h"
#include "parameters.h"
#include "main.h"
#include "pros/adi.hpp"

// 1000 --> 5000

enum CataState {
    RESETTING,
    SHOOTING
};

enum IntakeState {
    INTAKE,
    OUTTAKE,
    INACTIVE
};

// I could make this a namespace idk why im making it a class
class Effectors {
public:
    pros::Motor cataOne;
    pros::Motor cataTwo;
    pros::Motor intakeMotor;
    pros::Motor intakeMotorTwo;
    pros::Rotation rotSensor;
    CataState state;

    pros::ADIDigitalOut piston;
    bool wingsActive;
    IntakeState intakeActive;

    Effectors () : 
        cataOne(2, pros::E_MOTOR_GEAR_RED),
        cataTwo(19, pros::E_MOTOR_GEAR_RED), 
        intakeMotor(12, pros::E_MOTOR_GEAR_BLUE),    
        intakeMotorTwo(18, pros::E_MOTOR_GEAR_BLUE),
        piston('A'),
        rotSensor(15),
        wingsActive(false),
        intakeActive(INACTIVE),
        state(CataState::RESETTING)
    { 
        
        rotSensor.set_position(0); 
        cataOne.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_BRAKE);
        cataTwo.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_BRAKE);
        
    };
    ~Effectors() = default;
    // cata
    void shootCata ();
    void resetCata ();

    // wings
    void wingsToggle ();

    // intake
    void intakeToggle (bool reverse=false);
    void setIntake (bool isReverse=false, bool isOff=false); // SIMPLER version of intake; use this for auton
};

#endif