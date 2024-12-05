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

enum State {
    isRaising,
    hasDonut,
    IDLE
};

enum Color {
    noColor,
    blue,
    red
};

// I could make this a namespace idk why im making it a class
class Effectors {
public:
    pros::Motor arm;
    pros::Motor intakeMotor;
    pros::Motor conveyorMotor;

    pros::ADIDigitalOut clampPistonLeft;
    pros::ADIDigitalOut clampPistonRight;
    pros::ADIDigitalOut boinkerPiston;

    pros::ADIPotentiometer rotationSensor;
    pros::Optical colorSensor;
    pros::c::optical_rgb_s_t rgbVal;

    bool isClamped;
    std::atomic <IntakeState> intakeActive;
    
    pros::ADIDigitalIn limitSwitch;

    State currentState;
    Color colorState;

    bool previous_limit;
    bool first_click;
    bool boinkerActive;

    Effectors () : 
        arm(17, pros::E_MOTOR_GEAR_200),
        intakeMotor(13),
        conveyorMotor(1), //changed 12 to 13
        clampPistonLeft('D'),
        clampPistonRight('A'),
        boinkerPiston('B'),
        limitSwitch('H'),
        colorSensor(15), // change port
        rotationSensor(12),
        isClamped(false),
        previous_limit(false),
        first_click(false),
        boinkerActive(false),
        intakeActive(IntakeState::INACTIVE),
        currentState(State::IDLE),
        colorState(Color::noColor)
    {
        arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);  //PRAC code
    };
    ~Effectors() = default;

    // intake
    void setIntake (bool isReverse=false, bool isOff=false); // SIMPLER version of intake; use this for a   uton
    void toggleIntakeState (IntakeState ia, bool isConveyor=true);
    void intake (); // our bot isn't colorblind anymore!

    //clamp
    void toggleClamp();

    // arm
    void raiseArm ();
    void lowerArm ();
    void stopArm();
    void changeState();
    void stepArm();

    // boinker
    void toggleBoinker ();

};

#endif