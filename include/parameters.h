#ifndef PARAMETERS
#define PARAMETERS


// *********************** NOTES ***********************
//* Remember that you DID NOT INITIALIZE ODOMETERY!! 
//* This was for (TESTING PURPOSES)
//* ALSO NTOE THAT YOU NEED TO CHECK COORD SIYSTEM OF ODOM OKAPI
//*     VEX coordinate system is REALLY weird... (face y direction to where the bot is facing rn)
//*     Make it so that by default the y direction of the robot faces the y direction
//* Take a look at parameters.cpp
// *****************************************************

#include "pid.h"
#include "OdomOkapi.h"

// ==========================================================
// =========================== PID ==========================
// ==========================================================

#define Heading_P            0.5
#define Heading_I            0.5
#define Heading_D            0.5
#define Heading_MAXERR       0.5 // max error sum
#define Heading_MAXPOWER     0.5
#define Heading_MINPOWER     0.5
#define Heading_FACTOR       1

#define Distance_P           0.5
#define Distance_I           0.5
#define Distance_D           0.5
#define Distance_MAXERR      0.5  // max error sum
#define Distance_MAXPOWER    0.5
#define Distance_MINPOWER    0.5
#define Distance_FACTOR      1

extern PID DistancePID; // declared in parameters.cpp
extern PID HeadingPID;  // declared in parameters.cpp

// ============================================================
// =========================== MOTOR ==========================
// ============================================================

// drive
#define LEFT_TOP_MOTOR      3
#define RIGHT_TOP_MOTOR     11
#define LEFT_BOTTOM_MOTOR   8
#define RIGHT_BOTTOM_MOTOR  5

extern MotorGroup leftMotorGroup;
extern MotorGroup rightMotorGroup;

class Drive; // will be defined later
extern Drive drive;

// effectors
#define FLYWHEEL_MOTOR 4
#define INTAKE_MOTOR 7

class Effectors;
extern Effectors effectors;

// ============================================================
// ======================= ODOM PARAMS ========================
// ============================================================

// wheeeeels
#define WHEEL_DIM       3_in  // Diameter of robot wheel
#define WHEEL_TRACK     4_in  // Distance from center of the bottom left wheel to the center of the bottom right wheel

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

extern OdomOkapi odometery;

// =============================================================
// ======================= ROUTE PARAMS ========================
// =============================================================

#define DISTANCE_TOLERANCE 1.5_in
#define ANGLE_TOLERANCE 0.25_deg
#define TIME_TOLERANCE 10_s

// =============================================================
// ===================== CONTROLLER PARAMS =====================
// =============================================================

#define DRIVE_TYPE "tank" // change to "arcade" for arcade mode

#endif