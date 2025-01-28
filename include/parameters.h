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
#define RIGHT_BOTTOM_MOTOR   -4  //5, 12, 15 do not work
#define RIGHT_MIDDLE_MOTOR   -5
#define RIGHT_TOP_MOTOR      6
//  BACK LEFT 11, bottom left motor 13 top left motor 14
#define LEFT_BOTTOM_MOTOR    -1
#define LEFT_MIDDLE_MOTOR    -2
#define LEFT_TOP_MOTOR       3

#define BACK_TRACK_MOTOR     22

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
#define LEFT_TRACKING_WHEEL_TOP       'L'
#define LEFT_TRACKING_WHEEL_BOTTOM    'L'
#define RIGHT_TRACKING_WHEEL_TOP      'L'
#define RIGHT_TRACKING_WHEEL_BOTTOM   'L'
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

#define TIME_TOLERANCE 3_s // ADJUST THIS A LITTLE LESS


#endif