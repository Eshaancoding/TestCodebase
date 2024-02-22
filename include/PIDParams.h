#ifndef PIDPARAM
#define PIDPARAM

// distance (forward/backward)
#define Distance_P           0.0352
#define Distance_I           0
#define Distance_D           0.15
#define Distance_MAXPOWER    1
#define Distance_MINPOWER    0.05
#define Distance_FACTOR      1
#define Distance_SLEW        0.1 // <=========== really important (suggestion: upped alr)
#define Distance_MINERRDISI  2.5  // min error to disable I, NOT NEEDED IF I = 0 

// angle
#define Heading_P            0.245
#define Heading_I            0
#define Heading_D            0.03
#define Heading_MAXPOWER     0.8
#define Heading_MINPOWER     0
#define Heading_FACTOR       1
#define Heading_SLEW         0.025 // <=========== really important
#define Heading_MINERRDISI   0.5 // min error to disable I, NOT NEEDED IF I = 0 

// default parameters for pure pursuit
#define LOOKAHEAD_DIST 0.3_tile
#define HEADING_FACTOR 1
#define DISTANCE_FACTOR 1

#define CALLBACK_TOL 5_in // the tolerance of the callback
#define END_TOL 2_in // the tolerance at the end of the point 
// in other words: stop pure pursuit once this many inches away from target point

// Take a look at parameters.h for Distance, Angle, and Time Tolerance
#define DISTANCE_TOLERANCE 0.5_in 
#define ANGLE_TOLERANCE 1_deg
#define COURSE_CORRECTION_FACTOR 0.215

#endif