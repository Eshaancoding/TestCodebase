// These are default values. They can be changed at routes!
// note that deprecated (purepursuit.cpp) lookahead dist is defined in it's own file.
// note that deprecated (moveDepr.cpp) lookahead dist is defined in it's own file.

// for forward/backward
#define LOOKAHEAD_DIST   0.6_tile         // lookahead distance that determines angle control
#define MAX_SPEED        2.5_tps      // tile per second
#define MAX_ACCEL        12_tps2       // tile per second squared
#define KP               20.42        // FROM 0 - 600: P parameter between odom distance and target distance from motion profiling
#define KI               3.24         // minimum robot power send to actually set movement to robot; MAKE SURE BATTERY IS 100%
#define KA_MOVE          0.85         // parameter to tune the turning during movement
#define END_TOLERANCE    0.05_in      // Tolerance of distance traveled before end of movement
#define POINT_TOLERANCE  3_in         // Tolerance to set lookahead distance, kp, and callback function as movement occurs

// for turning movement
#define MAX_ANG_SPEED   135_dps         // degree per second
#define MAX_ANG_ACCEL   750_dps2        // degree per second squared  
#define KP_ANG          3.72         // P parameter between current angle and target angle from motion profiling
#define KI_ANG          7.32
#define ANG_TOLERANCE   0.1_deg         // angle tolerance before quitting tolerance

// the timeout we have before stopping while loop; adds this value with the estimated amount of time to finish movement.
// same for angle and distance movements
#define TIMEOUT 3_s 

// ****************** make sure you define ROBOT_WIDTH correctly in parameters.h ****************** 