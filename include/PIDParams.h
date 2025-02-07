#ifndef PIDPARAM
#define PIDPARAM

// distance (forward/backward)
#define Distance_P           0.068
#define Distance_I           0
#define Distance_D           0.038
#define Distance_MAXPOWER    0.6
#define Distance_MINPOWER    0
#define Distance_FACTOR      0.9
#define Distance_SLEW        1 // <=========== really important (suggestion: upped alr)
#define Distance_MINERRDISI  2.5  // min error to disable I, NOT NEEDED IF I = 0 

// angle
#define Heading_P            0.292
#define Heading_I            0
#define Heading_D            0.049
#define Heading_MAXPOWER     0.9
#define Heading_MINPOWER     0
#define Heading_FACTOR       1
#define Heading_SLEW         1 // <=========== really important
#define Heading_MINERRDISI   0.25 // min error to disable I, NOT NEEDED IF I = 0 

// Take a look at parameters.h for Distance, Angle, and Time Tolerance
#define DISTANCE_TOLERANCE 0.5_in 
#define ANGLE_TOLERANCE 0.51_deg
#define COURSE_CORRECTION_FACTOR 0.215

#endif