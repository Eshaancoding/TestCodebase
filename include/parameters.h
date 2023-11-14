#ifndef PARAMETERS
#define PARAMETERS

// *********************** NOTES ***********************
//* Remember that you DID NOT INITIALIZE ODOMETERY!! 
//* This was for (TESTING PURPOSES)
//* Decrease time tolerance! Increased it because of delay (also adjust PID params)
//* ALSO change the fact that the delay for each iteration is monstrously high
//* Remeber that enable sim is enabled; thus removing the move voltage/motor stuff now
//* ALSO NTOE THAT YOU NEED TO CHECK COORD SIYSTEM OF ODOM OKAPI
//*     VEX coordinate system is REALLY weird... (face y direction to where the bot is facing rn)
//*     Make it so that by default the y direction of the robot faces the y direction
//* Ideally... give doxygen comments in everywhere
// *****************************************************

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
#define LEFT_TOP_MOTOR       20
#define LEFT_BOTTOM_MOTOR    11
#define RIGHT_TOP_MOTOR      10
#define RIGHT_BOTTOM_MOTOR   1

extern okapi::MotorGroup leftMotorGroup;
extern okapi::MotorGroup rightMotorGroup;

class Drive; // will be defined later
extern Drive drive;

// effectors
class Effectors;
extern Effectors effectors;

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

#define COURSE_CORRECTION   false

#define DISTANCE_TOLERANCE 1_in 
#define ANGLE_TOLERANCE 1_deg
#define TIME_TOLERANCE 300_s // ADJUST THIS A LITTLE LESS


#endif