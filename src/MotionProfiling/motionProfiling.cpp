#include "motionProfiling.h"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QSpeed.hpp"
#include "okapi/api/units/QTime.hpp"
#include "Odom/Math.h"
using namespace std;

MotionProfiling :: MotionProfiling (vector<DrivePoint> points, QAcceleration acc) {
    this->acc = acc;

    QSpeed prev_speed = 0.0_fps;

    // =========== create basic lines ===========
    this->total_distance = 0_in;
    for (int i = 0; i < points.size() - 1; i++) {
        QLength dist = Math::distance(points[i].point, points[i+1].point);
        QSpeed max_speed = points[i].max_speed;
        QTime time_sec = (dist / max_speed);

        this->total_distance += dist;

        QSpeed y_diff = abs(max_speed - prev_speed);
        
        if (y_diff.convert(fps) > 0) {
            this->lines.push_back(Line(
                0_s,
                time_sec,
                max_speed,
                max_speed
            ));
        } else {
            // extend upon the previous shape
            this->lines[this->lines.size() - 1].t2 += time_sec;
        }

        prev_speed = max_speed;
    }

    // if sudden jump in vel, add lines to smooth it
    for (int i = 0; i < this->lines.size() - 1; i++) {
        QSpeed diff = abs(this->lines[i].y2 - this->lines[i+1].y1);
        if (diff.convert(fps) > 0) {
            this->lines[i].t2 -= diff / (2 * this->acc);
            this->lines[i+1].t2 -= diff / (2 * this->acc);
            this->lines.insert(this->lines.begin() + i + 1, Line(
                0_s,
                diff / this->acc,
                this->lines[i].y2,
                this->lines[i+1].y1
            ));
        } 
    }

    // used for acc/decel
    auto beg_speed = points[0].max_speed;
    auto end_speed = points[points.size() - 2].max_speed; 

    // add lines for acceleration
    this->lines[0].t2 -= beg_speed / (2 * this->acc);
    this->lines.insert(this->lines.begin(), Line(
        0_s,
        beg_speed / this->acc,
        0_fps, 
        beg_speed 
    ));

    // add lines for deacceleration
    this->lines[this->lines.size() - 1].t2 -= end_speed / (2 * this->acc);
    this->lines.push_back(Line(
        0_s,
        end_speed / this->acc,
        end_speed,
        0_fps
    ));

    // time smooth
    QTime currentTime = 0_s;
    for (int i = 0; i < this->lines.size(); i++) {
        QTime w = this->lines[i].t2 - this->lines[i].t1;
        this->lines[i].t1 = currentTime;
        this->lines[i].t2 = w + currentTime;
        currentTime += w;
    }

    this->total_time = currentTime; // set total time
}

QSpeed MotionProfiling :: vel (QTime t) {
    for (auto l : this->lines) {
        if (t >= l.t1 && t <= l.t2) return l.eval(t);
    }
    return 0_fps;
}

QLength MotionProfiling :: dist (QTime t) {
    QLength out = 0_ft; 
    for (auto l : this->lines) {
        out += l.area(t);
    }
    return out;
}

QTime MotionProfiling :: get_total_time () {
    return this->total_time;
}

QLength MotionProfiling :: get_total_distance () {
    return this->total_distance;
}