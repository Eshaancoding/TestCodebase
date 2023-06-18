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
//* Take a look at parameters.cpp
// *****************************************************

#include "pid.h"
#include "Odom/OdomOkapi.h"
#include "Odom/OdomSim.h"

// ==========================================================
// =========================== PID ==========================
// ==========================================================

// angle
#define Heading_P            1.5
#define Heading_I            0
#define Heading_D            0
#define Heading_MINERRDISI   2.5 // min error to disable I (in inches)
#define Heading_MAXPOWER     0.5
#define Heading_MINPOWER     0
#define Heading_FACTOR       1
#define Heading_SLEW         1

// distance (forward/backward)
#define Distance_P           0.05
#define Distance_I           0
#define Distance_D           0
#define Distance_MINERRDISI  2.5  // min error to disable I (in rad)
#define Distance_MAXPOWER    0.5
#define Distance_MINPOWER    0
#define Distance_FACTOR      1
#define Distance_SLEW        0.2

// ************* DELAY CHANGE ***************
// ****** THIS IS REALLY IMPORTANT PARAM ****
// essentially it determines the number of iterations 
// to update its parameters & power arcade, etc.
#define DELAYITER           5_ms  

// how much errors to average when finding min error
#define Distance_N          10
#define Heading_N           5

// ************ DELAY CAHNGE ***************
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

// debug
#define ODOM_DEBUG      true

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

#define DISTANCE_TOLERANCE 1_in 
#define ANGLE_TOLERANCE 1_deg
#define TIME_TOLERANCE 30_s // ADJUST THIS A LITTLE LESS 

// =============================================================
// ===================== CONTROLLER PARAMS =====================
// =============================================================

#define DRIVE_TYPE "tank" // change to "arcade" for arcade mode

// =============================================================
// ====================== Odom Simulation ======================
// =============================================================

#define ENABLE_ODOMSIM true // WILL DISABLE ACTUAL MOVEMENT FORWARD :O

#define ACC 3_in
#define MAX_VEL 10_in
#define DECEL_CONSTANT 0.3

#define ACC_ANG 2_deg
#define MAX_ACC_ANG 30_deg
#define ANGLE_DECEL_CONSTANT 0.3

extern OdomSim simulation;

#endif