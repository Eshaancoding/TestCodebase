// These are default values. They can be changed at routes!

// note that deprecated (purepursuit.cpp) lookahead dist is defined in it's own file.
// note that deprecated (moveDepr.cpp) lookahead dist is defined in it's own file.
#define LOOKAHEAD_DIST 3_in     

#define MAX_SPEED 2.3_fps           // feet per second
#define MAX_ACCELERATION 4_fps2     // foot per second squared

#define KP 1.82
#define TIMEOUT 3_s // the timeout we have before stopping while loop; adds this value with the estimated amount of time to finish movement.
#define END_TOLERANCE 2_in // measured in the distance travelled by the robot.
#define POINT_TOLERANCE 3_in

// make sure you define ROBOT_WIDTH correctly in parameters.h