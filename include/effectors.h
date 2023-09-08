#ifndef EFFECTORS_H
#define EFFECTORS_H
#include "Console.h"
#include "parameters.h"
#include "main.h"
#include "pros/adi.hpp"

// I could make this a namespace idk why im making it a class
class Effectors {
public:
    pros::Motor cataOne;
    pros::Motor cataTwo;
    pros::Rotation rotSensor;

    Effectors () : 
        cataOne(1, pros::E_MOTOR_GEAR_RED), 
        cataTwo(2, pros::E_MOTOR_GEAR_RED), 
        rotSensor(3)
    {};
    ~Effectors() = default;
    void shoot ();
};

#endif
// clockwise pos 