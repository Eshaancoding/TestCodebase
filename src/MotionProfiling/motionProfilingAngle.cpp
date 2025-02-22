#include "motionProfilingAngle.h"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QAngularAcceleration.hpp"
#include "okapi/api/units/QAngularSpeed.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QSpeed.hpp"
#include "okapi/api/units/QTime.hpp"
#include "Odom/Math.h"
using namespace std;

MotionProfilingAngle :: MotionProfilingAngle (
    okapi::OdomState current_pos,
    Point target_pos, 
    QAngularAcceleration accel, 
    QAngularSpeed speed
) {

    QSpeed prev_speed = 0.0_fps;

    // =========== create basic lines ===========
    QAngle angle_err = Math::anglePoint(current_pos, target_pos);
    this->currentPos = current_pos;
    this->angle_need_turn = angle_err;
    QTime time_sec = (angle_err / speed);
    
    this->line_angles.push_back(LineAngle(
        0_s,
        time_sec,
        speed,
        speed
    )); 
    

    this->line_angles[0].t2 -= speed / (2 * accel);
    this->line_angles.insert(this->line_angles.begin(), LineAngle(
        0_s,
        speed / accel,
        0_dps, 
        speed 
    ));

    // add lines for deacceleration
    this->line_angles[this->line_angles.size() - 1].t2 -= speed / (2 * accel);
    this->line_angles.push_back(LineAngle(
        0_s,
        speed / accel,
        speed,
        0_dps
    ));

    // time smooth
    QTime currentTime = 0_s;
    for (int i = 0; i < this->line_angles.size(); i++) {
        QTime w = this->line_angles[i].t2 - this->line_angles[i].t1;
        this->line_angles[i].t1 = currentTime;
        this->line_angles[i].t2 = w + currentTime;
        currentTime += w;
    }

    this->total_time = currentTime; // set total time
}

QAngularSpeed MotionProfilingAngle :: vel (QTime t) {
    for (auto l : this->line_angles) {
        if (t >= l.t1 && t <= l.t2) return l.eval(t);
    }
    return 0_dps; // degree per second
}

Point MotionProfilingAngle :: target_point (QTime t) {
    QAngle out = 0_deg; 
    for (auto l : this->line_angles) {
        out += l.area(t);
    }

    Point p = {
        this->currentPos.x + 10_tile * sin(this->currentPos.theta + out),
        this->currentPos.y + 10_tile * cos(this->currentPos.theta + out)
    };

    return p;
}

QTime MotionProfilingAngle :: get_total_time () {
    return this->total_time;
}