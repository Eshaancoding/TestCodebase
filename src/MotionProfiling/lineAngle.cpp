#include "motionProfilingAngle.h"
#include "okapi/api/units/QAcceleration.hpp"
#include "okapi/api/units/QAngularAcceleration.hpp"
#include "okapi/api/units/QAngularSpeed.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QSpeed.hpp"
#include "okapi/api/units/QTime.hpp"
#include "okapi/api/units/RQuantity.hpp"
using namespace okapi;

QAngularSpeed LineAngle :: eval (QTime t) {
    if (t < t1 || t > t2) return 0_dps;
    QAngularAcceleration slope = (y2 - y1) / (t2 - t1);
    return slope * (t - t1) + y1;
}

QAngle LineAngle :: area (QTime t) {
    if (t < t1) return 0_deg;
    if (t > t2) t = t2;

    double slope = ((y2 - y1) / (t2 - t1)).convert(dps2);
    double intercept = y2.convert(dps) - slope * t2.convert(second);
    
    auto t_sq = pow(t.convert(second),2) ;
    auto t1_sq = pow(t1.convert(second), 2);

    return ((slope / 2) * (t_sq - t1_sq) + intercept * (t.convert(second) - t1.convert(second))) * 1_deg;
}

