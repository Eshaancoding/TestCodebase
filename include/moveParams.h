// These are default values. They can be changed at routes!
// note that deprecated (purepursuit.cpp) lookahead dist is defined in it's own file.
// note that deprecated (moveDepr.cpp) lookahead dist is defined in it's own file.

// for pure pursuit (can be abstracted for forward/backward)
#define LOOKAHEAD_DIST   0.3_tile         // lookahead distance that determines angle control
#define P_DIST           20.3             // P_DIST * distance of current goal and endpoint = forward motor vel; usually from 0-40
#define P_ANG            0.95             // P_ANG * curvature of arc = turning motor vel; usually from 0 - 0.1
#define END_TOLERANCE    0.5_in           // Tolerance of distance traveled before end of movement
#define POINT_TOLERANCE  3_in             // Tolerance to set lookahead distance, kp, and callback function as movement occurs

// for turning movement
#define MAX_ANG_SPEED   750_dps         // degree per second
#define MAX_ANG_ACCEL   750_dps2        // degree per second squared  
#define KP_ANG          5.32            // P parameter between current angle and target angle from motion profiling
#define KI_ANG          7.32
#define ANG_TOLERANCE   0.5_deg         // angle tolerance before quitting tolerance

// the timeout we have before stopping while loop; adds this value with the estimated amount of time to finish movement.
// same for angle and distance movements
#define TIMEOUT 5_s 

// ****************** make sure you define ROBOT_WIDTH correctly in parameters.h ******************
