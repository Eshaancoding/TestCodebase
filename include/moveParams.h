// These are default values. They can be changed at routes!

#define LOOKAHEAD_DIST 3_in     
#define MAX_SPEED 2.3_fps           // feet per second
#define MAX_ACCELERATION 4_fps2     // foot per second squared
#define CURVATURE_SPEED 1_fps

#define KP 1.8
#define TIMEOUT 3_s // the timeout we have before stopping while loop; adds this value with the estimated amount of time to finish movement.
#define END_TOLERANCE 2_in // measured in the distance travelled by the robot.

// make sure you define ROBOT_WIDTH correctly in parameters.h