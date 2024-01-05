#ifndef PARAMETERS
#define PARAMETERS
#include "pid.h"
#include "Odom/OdomOkapi.h"

// ==========================================================
// =========================== PID ==========================
// ==========================================================

// actual params in PID Params.h

// ************* DELAY CHANGE ***************
// ****** THIS IS REALLY IMPORTANT PARAM ****
// essentially it determines the number of iterations 
// to update its parameters & power arcade, etc.
#define DELAYITER           10_ms

// defines what % of the path that should disable the heading for course correction
#define DISABLEPOINT        0.75


// ************ DELAY CAHNGE ***************
extern PID DistancePID; // declared in parameters.cpp
extern PID HeadingPID;  // declared in parameters.cpp

// ============================================================
// =========================== MOTOR ==========================
// ============================================================

// drive
#define LEFT_BOTTOM_MOTOR    1
#define RIGHT_BOTTOM_MOTOR   10
#define RIGHT_PTO_MOTOR      20
#define LEFT_PTO_MOTOR       11
#define LEFT_TOP_MOTOR       15
#define RIGHT_TOP_MOTOR      16 

extern okapi::Motor leftPTOMotor;
extern okapi::Motor rightPTOMotor;
extern okapi::MotorGroup leftMotorGroup;
extern okapi::MotorGroup rightMotorGroup;

class Drive; // will be defined later
extern Drive drive;

// effectors
class Effectors;
extern Effectors eff;

// ============================================================
// ======================= ODOM PARAMS ========================
// ============================================================

// debug
#define ODOM_DEBUG      true

// tracking wheel ports
#define LEFT_TRACKING_WHEEL_TOP       'A'
#define LEFT_TRACKING_WHEEL_BOTTOM    'B'
#define RIGHT_TRACKING_WHEEL_TOP      'C'
#define RIGHT_TRACKING_WHEEL_BOTTOM   'D'
#define MID_TRACKING_WHEEL_TOP        ' '
#define MID_TRACKING_WHEEL_BOTTOM     ' '

// tracking wheel dim
#define TRACKING_WHEEL_TRACK    2_in    // Distance from the center of the left tracking wheel to the center of the right tracking wheel
#define TRACKING_WHEEL_DIM      0.5_in  // Diameter of tracking wheel
#define TRACKING_WHEEL_BACK     0_in    // distance from the center of rotation and the back tracking wheel (won't activate unless mid works)

// =============================================================
// ======================= ROUTE PARAMS ========================
// =============================================================

// how much errors to average when finding min error
#define Distance_N          25
#define Heading_N           100

#define COURSE_CORRECTION   true

#define DISTANCE_TOLERANCE 1_in 
#define ANGLE_TOLERANCE 1_deg
#define TIME_TOLERANCE 3_s // ADJUST THIS A LITTLE LESS


#endif