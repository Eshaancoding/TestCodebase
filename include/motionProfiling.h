#ifndef MOTION_PROFILING
#define MOTION_PROFILING

#include "drive.h"
#include "okapi/api/units/QAcceleration.hpp"
#include "okapi/api/units/QAngularAcceleration.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QSpeed.hpp"
#include "okapi/api/units/QTime.hpp"

class Line {
public: 
    QTime t1;
    QTime t2;
    QSpeed y1;
    QSpeed y2;
    
    Line (
        QTime t1,
        QTime t2,
        QSpeed y1,
        QSpeed y2
    ) :
        t1(t1),
        t2(t2),
        y1(y1),
        y2(y2)
    {}

    QSpeed eval (QTime t);
    QLength area (QTime t);
};

class MotionProfiling {
private: 
    std::vector<Line> lines;
    QTime total_time;
    QAcceleration acc;
    bool is_debug;
    
public:
    MotionProfiling (std::vector<DrivePoint> points, QAcceleration acc);
    QSpeed vel (QTime t);
    QLength dist (QTime t);
    void set_debug (bool is_debug);
    QTime get_total_time ();
};

#endif