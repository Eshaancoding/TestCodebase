#ifndef PIDPARAM
#define PIDPARAM

// distance (forward/backward)
#define Distance_P           0.043
#define Distance_I           0
#define Distance_D           0.043
#define Distance_MAXPOWER    0.6
#define Distance_MINPOWER    0
#define Distance_FACTOR      1
#define Distance_SLEW        1 // <=========== really important (suggestion: upped alr)
#define Distance_MINERRDISI  2.5  // min error to disable I, NOT NEEDED IF I = 0 

// angle
#define Heading_P            0.285
#define Heading_I            0
#define Heading_D            0
#define Heading_MAXPOWER     1
#define Heading_MINPOWER     0
#define Heading_FACTOR       1
#define Heading_SLEW         1 // <=========== really important
#define Heading_MINERRDISI   0.25 // min error to disable I, NOT NEEDED IF I = 0 

// default parameters for pure pursuit
#define LOOKAHEAD_DIST 0.5_tile // adjust in drive.h again

// Take a look at parameters.h for Distance, Angle, and Time Tolerance
#define DISTANCE_TOLERANCE 0.5_in 
#define ANGLE_TOLERANCE 0.5_deg
#define COURSE_CORRECTION_FACTOR 0.215

#endif