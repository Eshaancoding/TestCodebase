#ifndef EFFECTORS_H
#define EFFECTORS_H
#include "Console.h"
#include "parameters.h"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"

enum IntakeState {
    INTAKE = 0,
    OUTTAKE = 1,
    INACTIVE = 2,
    SLOW = 3
};

enum State {
    isRaising,
    hasDonut,
    IDLE
};

enum ArmState {
    PID_ARM,
    Raising_ARM,
    IDLE_ARM,
    Lowering_ARM
};

enum Color {
    noColor,
    blue,
    red
};

// I could make this a namespace idk why im making it a class
class Effectors {
public:
    //pros::Motor armLeft; // make 2 arm motors
    pros::Motor armRight;
    static pros::Motor intakeMotor;
    pros::Motor conveyorMotor;

    pros::ADIDigitalOut clampPiston;
    pros::ADIDigitalOut boinkerPiston;

    pros::Rotation rotationSensor;
    static pros::Optical colorSensor;

    ArmState arm_state;    

    bool isClamped;
    static std::atomic <IntakeState> intakeActive;
    static std::atomic <bool> isBlue;
    static std::atomic <bool> seeColor;

    pros::ADIDigitalIn limitSwitch;

    State currentState;
    static Color colorState;

    bool previous_limit;
    bool first_click;
    bool boinkerActive;

    Effectors () : 
        // for motor group: BACK LEFT 11, bottom left motor 13 top left motor 14
        //armLeft(6, pros::E_MOTOR_GEAR_200),
        armRight(20, pros::E_MOTOR_GEAR_100),
        conveyorMotor(21), // intake 21
        clampPiston('B'),
        boinkerPiston('A'),
        limitSwitch('H'),
        rotationSensor(19), // UPDATE THIS 
        isClamped(false),
        previous_limit(false),
        first_click(false),
        boinkerActive(false),
        currentState(State::IDLE),
        arm_state(ArmState::PID_ARM)
    {
        //armLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);  //PRAC code
        armRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        rotationSensor.reset();
        rotationSensor.reset_position();
    };
    ~Effectors() = default;

    // intake
    void setIntake (bool isReverse=false, bool isOff=false); // SIMPLER version of intake; use this for a   uton
    void setIntake (IntakeState state); // SIMPLER version of intake; use this for a   uton
    void toggleIntakeState (IntakeState ia, bool isConveyor=true);
    static void intake (); // our bot isn't colorblind anymore!

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


    void slowIntake();
};

#endif