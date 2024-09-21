#ifndef EFFECTORS_H
#define EFFECTORS_H
#include "Console.h"
#include "parameters.h"
#include "main.h"
#include "pros/adi.hpp"

enum IntakeState {
    INTAKE = 0,
    OUTTAKE = 1,
    INACTIVE = 2
};

// I could make this a namespace idk why im making it a class
class Effectors {
public:
    pros::Motor arm;
    pros::Motor intakeMotor;
    pros::Motor conveyorMotor;
  

    pros::ADIDigitalOut clampPistonLeft;
    pros::ADIDigitalOut clampPistonRight;

    bool isClamped;
    IntakeState intakeActive;
    
    pros::ADIDigitalIn limitSwitch;

    bool previous_limit;
    bool first_click;

    Effectors () : 
        arm(17, pros::E_MOTOR_GEAR_200),
        intakeMotor(13),
        conveyorMotor(1), //changed 12 to 13
        clampPistonLeft('D'),
        clampPistonRight('A'),
        limitSwitch('H'),
        isClamped(false),
        previous_limit(false),
        first_click(false),
        intakeActive(IntakeState::INACTIVE)
    {
        arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);  //PRAC code
    };
    ~Effectors() = default;

    // intake
    void intakeToggle (bool reverse=false); //turn on convey
    void setIntake (bool isReverse=false, bool isOff=false); // SIMPLER version of intake; use this for a   uton
    void setIntakeState (IntakeState ia);
    void stepOuttake ();    // this is for the weird limit switch thing

    //arm
    void toggleArm();  //PRAC code

    //clamp
    void toggleClamp();

    // arm
    void raiseArm ();
    void lowerArm ();
    void stopArm();


};

#endif