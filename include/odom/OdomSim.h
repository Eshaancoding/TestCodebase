#ifndef ODOMSIM_H
#define ODOMSIM_H

#include "main.h"
#include "OdomMath.h"

// basically... a really BAD vehicle simulator :/
// going to be arcade drive :thumbsup:
class OdomSim {
public:
    okapi::QAngle currentAngle;
    okapi::QLength xPos;
    okapi::QLength yPos;

    okapi::QLength vel; // just magnitude of change in speed per iteration
    okapi::QAngle angleVel; // just magnitude of change in angle per iteration

    OdomSim ();
    okapi::OdomState getPos ();
    void setPos (okapi::OdomState state);

    void step (double heading, double distance);
};

#endif