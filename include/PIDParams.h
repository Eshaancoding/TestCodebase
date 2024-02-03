#ifndef PIDPARAM
#define PIDPARAM

// distance (forward/backward)
#define Distance_P           0.026
#define Distance_I           0
#define Distance_D           0
#define Distance_MAXPOWER    1
#define Distance_MINPOWER    0.05
#define Distance_FACTOR      1
#define Distance_SLEW        0.01 // <=========== really important
#define Distance_MINERRDISI  2.5  // min error to disable I, NOT NEEDED IF I = 0 

// angle
#define Heading_P            0.315
#define Heading_I            0
#define Heading_D            0.08
#define Heading_MAXPOWER     0.9
#define Heading_MINPOWER     0.1
#define Heading_FACTOR       1
#define Heading_SLEW         0.035 // <=========== really important
#define Heading_MINERRDISI   0.5 // min error to disable I, NOT NEEDED IF I = 0 

// Take a look at parameters.h for Distance, Angle, and Time Tolerance
#define DISTANCE_TOLERANCE 0.5_in 
#define ANGLE_TOLERANCE 1_deg

#define COURSE_CORRECTION_FACTOR 0.3

#endif