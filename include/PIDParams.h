#ifndef PIDPARAM
#define PIDPARAM

// angle
#define Heading_P            0.015
#define Heading_I            0
#define Heading_D            0.1
#define Heading_MINERRDISI   0.5 // min error to disable I (in rad)
#define Heading_MAXPOWER     1
#define Heading_MINPOWER     0
#define Heading_FACTOR       1
#define Heading_SLEW         0.005

// distance (forward/backward)
#define Distance_P           0.031
#define Distance_I           0
#define Distance_D           0.001
#define Distance_MINERRDISI  2.5  // min error to disable I (in rad)
#define Distance_MAXPOWER    0.6
#define Distance_MINPOWER    0
#define Distance_FACTOR      1
#define Distance_SLEW        0.01


 

#endif