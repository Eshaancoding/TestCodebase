#include "parameters.h"
#include "drive.h"
#include "PIDParams.h"
#include "effectors.h"
#include "pros/motors.h"
#include "main.h"

PID DistancePID = PID(
    Distance_P,   
    Distance_I,   
    Distance_D,
    Distance_MINERRDISI,
    Distance_MINPOWER,   
    Distance_MAXPOWER,
    Distance_SLEW,
    Distance_FACTOR
);

PID HeadingPID = PID(
    Heading_P,   
    Heading_I,   
    Heading_D,   
    Heading_MINERRDISI,
    Heading_MINPOWER,   
    Heading_MAXPOWER,   
    Heading_SLEW,
    Heading_FACTOR
);

// gearing and brake mode are set in initialize
MotorGroup leftMotorGroup = okapi::MotorGroup({-LEFT_TOP_MOTOR, -LEFT_BOTTOM_MOTOR, -LEFT_MIDDLE_MOTOR});
MotorGroup rightMotorGroup = okapi::MotorGroup({RIGHT_TOP_MOTOR, RIGHT_BOTTOM_MOTOR, RIGHT_MIDDLE_MOTOR});

Drive drive = Drive();
Effectors eff = Effectors();