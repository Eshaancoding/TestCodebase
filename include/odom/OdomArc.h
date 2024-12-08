#ifndef ODOMARC_H
#define ODOMARC_H

#include "main.h"
#include "Math.h"
#include "parameters.h"
#include <iostream>
using namespace std;

namespace OdomArc {
    void init (QAngle init_angle=0_deg);
    void MainLoop ();

    okapi::OdomState getPos();
    void setPos (
        std::optional<okapi::QLength> x=std::nullopt, 
        std::optional<okapi::QLength> y=std::nullopt, 
        std::optional<okapi::QAngle> angle=std::nullopt
    );
    bool isCalibrating ();
    double distanceGet ();
    double distanceb ();
    double angleGet ();
};


#endif 