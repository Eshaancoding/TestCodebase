#ifndef ODOMARC_H
#define ODOMARC_H

#include "main.h"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QSpeed.hpp"
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

    QLength distanceGet ();
    QLength distanceb ();
    QSpeed velb ();
    QAngle angleGet ();
    void resetDistTravelled ();

    QLength getDistTravelled ();
    QSpeed getSpeed ();
};


#endif 