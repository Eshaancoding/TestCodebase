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

// I could make this a namespace idk why im making it a class
class Effectors {
public:
    pros::Motor cataOne;
    pros::Motor cataTwo;
    pros::Motor intakeMotor;
    pros::Rotation rotSensor;
    CataState state;

    pros::ADIDigitalOut piston;
    bool isActive;

    Effectors () : 
        cataOne(8, pros::E_MOTOR_GEAR_RED), 
        cataTwo(13, pros::E_MOTOR_GEAR_RED), 
        intakeMotor(4, pros::E_MOTOR_GEAR_BLUE),
        piston('A'),
        isActive(false),
        rotSensor(3),
        state (CataState::RESETTING)
    { rotSensor.set_position(0); };
    ~Effectors() = default;
    void shoot ();
    void intake ();
    void resetIntake ();
    void reset ();
};

#endif
// clockwise pos 