#ifndef ODOMCUSTOM_H
#define ODOMCUSTOM_H

#include "main.h"
#include "Math.h"
#include "parameters.h"
#include <iostream>
using namespace std;

class OdomCustom {
private:
    okapi::QAngle currentAngle;
    okapi::QLength xPos;
    okapi::QLength yPos;

    okapi::ADIEncoder* leftEncoder;  // does not have default constructor 
    okapi::ADIEncoder* rightEncoder; 
    okapi::ADIEncoder* middleEncoder;

    double previousLeftEncoder;
    double previousRightEncoder;
    double previousMidEncoder;

    void MainLoop ();
public:
    OdomCustom();
    ~OdomCustom() = default;
    okapi::OdomState getPos();
    void setPos (okapi::OdomState state);
    double getLeftRevs  ();
    double getRightRevs ();
    double getMiddleRevs  ();
};


#endif 