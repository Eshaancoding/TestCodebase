#include "parameters.h"
#include "drive.h"
#include "effectors.h"

PID DistancePID = PID(
    Distance_P,   
    Distance_I,   
    Distance_D,   
    Distance_MAXERR,   
    Distance_MINPOWER,   
    Distance_FACTOR
);

PID HeadingPID = PID(
    Heading_P,   
    Heading_I,   
    Heading_D,   
    Heading_MAXERR,
    Heading_MAXPOWER,   
    Heading_MINPOWER,   
    Heading_FACTOR
);

OdomOkapi odometery = OdomOkapi();

MotorGroup leftMotorGroup = okapi::MotorGroup({LEFT_TOP_MOTOR, LEFT_BOTTOM_MOTOR});
MotorGroup rightMotorGroup = okapi::MotorGroup({RIGHT_TOP_MOTOR, RIGHT_BOTTOM_MOTOR});

Drive drive = Drive();

Effectors effectors = Effectors();