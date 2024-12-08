#ifndef CAMERA_H
#define CAMERA_H

#include "main.h"
#include <string>

using namespace std;
using namespace okapi; 

struct XY {
    float x;
    float y;
};

class VisionSensor {
private:
    pros::Vision vision_sensor;        

public:
    VisionSensor () : 
        vision_sensor('1') 
    {}

    XY getBlueRingOffset ();
    XY getRedRingOffset ();
};  

#endif