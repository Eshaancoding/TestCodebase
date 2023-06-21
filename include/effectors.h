#ifndef EFFECTORS_H
#define EFFECTORS_H

#include "parameters.h"
#include "main.h"

// I could make this a namespace idk why im making it a class
class Effectors {
private:
    Motor flywheelMotor; 
    Motor intakeMotor;
public:
    Effectors () : 
        flywheelMotor(FLYWHEEL_MOTOR), 
        intakeMotor(INTAKE_MOTOR) 
    {};

    void intake (std::int16_t power=127);
    void outtake (std::int16_t power=127);
    void stopIntake ();

    void spinFlywheel (std::int16_t power=127);
    void stopFlywheel ();

    void delay (QTime time);
};

#endif