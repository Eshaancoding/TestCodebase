#ifndef PIDPARAM
#define PIDPARAM

// distance (forward/backward)
#define Distance_P           0.070 // 0.075 and 0.3 is good
#define Distance_I           0
#define Distance_D           0.23
#define Distance_MAXPOWER    0.9
#define Distance_MINPOWER    0
#define Distance_FACTOR      1
#define Distance_SLEW        0.2 // <=========== really important (suggestion: upped alr)
#define Distance_MINERRDISI  2.5  // min error to disable I, NOT NEEDED IF I = 0 

// angle
#define Heading_P            0.235
#define Heading_I            0
#define Heading_D            0
#define Heading_MAXPOWER     1
#define Heading_MINPOWER     0
#define Heading_FACTOR       1
#define Heading_SLEW         0.025 // <=========== really important
#define Heading_MINERRDISI   0.5 // min error to disable I, NOT NEEDED IF I = 0 

// default parameters for pure pursuit
#define LOOKAHEAD_DIST 0.3_tile // adjust in drive.h again

// Take a look at parameters.h for Distance, Angle, and Time Tolerance
#define DISTANCE_TOLERANCE 1.5_in 
#define ANGLE_TOLERANCE 1_deg
#define COURSE_CORRECTION_FACTOR 0.215

#endif