// These are default values. They can be changed at routes!
// note that deprecated (purepursuit.cpp) lookahead dist is defined in it's own file.
// note that deprecated (moveDepr.cpp) lookahead dist is defined in it's own file.

// for forward/backward
#define LOOKAHEAD_DIST   0.6_tile      // lookahead distance that determines angle control
#define MAX_SPEED        2.0_tps       // tile per second
#define MAX_ACCEL        4_tps2       // tile per second squared

#define KV               18.3          // Feed-forward constant with the target velocity (applied to each side of the wheel)
#define KA               0.6           // Feed-forward constant with the target acceleration (applied to each side of the wheel)
#define KP               0.5           // Feed-back constant with target velocity and measured vel (applied to each side of wheel)

#define AngP             3.3
#define AngD             1.2

#define END_TOLERANCE    0.5_in      // Tolerance of distance traveled before end of movement
#define POINT_TOLERANCE  3_in         // Tolerance to set lookahead distance, kp, and callback function as movement occurs

// for turning movement
#define MAX_ANG_SPEED   135_dps         // degree per second
#define MAX_ANG_ACCEL   750_dps2        // degree per second squared  
#define KP_ANG          4.62         // P parameter between current angle and target angle from motion profiling
#define KI_ANG          7.32
#define ANG_TOLERANCE   0.5_deg         // angle tolerance before quitting tolerance

// the timeout we have before stopping while loop; adds this value with the estimated amount of time to finish movement.
// same for angle and distance movements
#define TIMEOUT 2_s
