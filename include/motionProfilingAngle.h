#ifndef MOTION_PROFILING
#define MOTION_PROFILING

#include "drive.h"
#include "okapi/api/odometry/odomState.hpp"
#include "okapi/api/odometry/point.hpp"
#include "okapi/api/units/QAcceleration.hpp"
#include "okapi/api/units/QAngularAcceleration.hpp"
#include "okapi/api/units/QAngularSpeed.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QSpeed.hpp"
#include "okapi/api/units/QTime.hpp"


class LineAngle {
public: 
    QTime t1;
    QTime t2;
    QAngularSpeed y1;
    QAngularSpeed y2;
    
    LineAngle (
        QTime t1,
        QTime t2,
        QAngularSpeed y1,
        QAngularSpeed y2
    ) :
        t1(t1),
        t2(t2),
        y1(y1),
        y2(y2)
    {}

    QAngularSpeed eval (QTime t);
    QAngle area (QTime t);
};

class MotionProfilingAngle {
private: 
    vector<LineAngle> line_angles;
    QAngle angle_need_turn; // the total angle that needs to be turned (this is simply the target angle - current angle)
    QAngle target_angle;
    QTime total_time;
    QAngularAcceleration acc;
    bool is_debug;
    
public:
    // more simple version than distance Motion Profiling
    // takes current position (including theta) and the target position to face towards, and calculates delta theta
    // there's no need to have multiple "points" to turn towards (unlike distance). Simplest case is often the best.
    MotionProfilingAngle ( 
        okapi::OdomState current_pos,
        Point target_pos, 
        QAngularAcceleration accel, 
        QAngularSpeed speed
    );

    QAngularSpeed vel (QTime t);
    QAngle ang (QTime t);
    void set_debug (bool is_debug);
    QTime get_total_time ();
    QAngle get_angle_total ();
};

#endif