#include "motionProfiling.h"
#include "odom/Math.h"
#include "okapi/api/units/QAcceleration.hpp"
#include "okapi/api/units/QAngularAcceleration.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QSpeed.hpp"
#include "okapi/api/units/QTime.hpp"
#include "pros/apix.h"
#include <memory>

MotionProfiling :: MotionProfiling (vector<DrivePoint> points, QAcceleration acc) {
    this->acc = acc;
    this->total_time = 0_s;

    okapi::QSpeed prev_speed = 0.0_mps;

    for (int i = 0; i < points.size() - 1; i++) {
        auto dist = Math::distance(points[i].point, points[i+1].point);
        auto max_speed = points[i].max_speed;
        QTime time_sec = (dist.convert(okapi::foot) / max_speed.convert(okapi::fps)) * 1_s;
        QTime acc_delta_time = (max_speed.convert(okapi::fps) / (2 * acc.convert(fps2))) * 1_s;

        auto y_diff = abs((max_speed - prev_speed).convert(fps));

        if (i == 0) { // first path
            this->shapes.push_back(PathSegment(
                max_speed,
                time_sec + acc_delta_time
            ));
            this->total_time += time_sec + acc_delta_time;
        } 
        else if (i == points.size() - 2) { // last path
            if (y_diff > 0) {
                this->shapes.push_back(PathSegment(
                    max_speed,
                    time_sec + acc_delta_time
                )); 
            } else {
                this->shapes[this->shapes.size() - 1].time += time_sec + acc_delta_time;
            }
            this->total_time += time_sec + acc_delta_time;

        }
        else if (y_diff > 0) {
            this->shapes.push_back(PathSegment(
                max_speed,
                time_sec
            ));
            this->total_time += time_sec;
        } else {
            // extend upon the previous shape
            this->shapes[this->shapes.size() - 1].time += time_sec;
        }

        prev_speed = max_speed;
    }
}

QSpeed MotionProfiling :: vel (QTime s) {
    // check if we are in acceleration or deceleration
    QSpeed speed_beginning = this->shapes[0].speed;
    QSpeed speed_end = this->shapes[this->shapes.size() - 1].speed;

    // acceleration
    if (s <= speed_beginning.convert(fps) / acc.convert(fps2) * 1_s) {
        return acc.convert(fps2) * s.convert(second) * 1_fps;
    } 

    // deacceleration
    auto decel_start = this->total_time - (speed_end.convert(fps) / acc.convert(fps2) * 1_s );
    if (s >= decel_start && s <= this->total_time) {
        return speed_end - (acc.convert(fps2) * (s - decel_start).convert(second) * 1_fps);
    }

    // check whether we are accelerating/decelerrating in between movements
    QTime t = 0_s;
    for (int i = 0; i < this->shapes.size() - 1; i++) {
        auto first_shape = this->shapes[i];
        auto second_shape = this->shapes[i+1];
        double avg_y = (first_shape.speed.convert(fps) + second_shape.speed.convert(fps)) / 2.0;

        t += first_shape.time;
        QTime tol = 1_s * abs( (second_shape.speed - first_shape.speed).convert(fps) / (2 * acc.convert(fps2)) ); 

        if (s >= t - tol && s <= t + tol) {
            double acc_line = (second_shape.speed > first_shape.speed) ? acc.convert(fps2) : -acc.convert(fps2);
            return (acc_line * (s - t).convert(second) + avg_y) * 1_fps;
        }
    }

    // else, we are in cruise
    t = 0_s;
    for (auto sh : this->shapes) {
        t += sh.time;
        if (s <= t) return sh.speed;
    }
    
    return 0_fps; // choose carefully (called when robot doesn't reach the motion profiling in time)
}

QLength MotionProfiling :: dist (QTime s) {
    return 0_m;  // choose carefully (called when robot doesn't reach the motion profiling in time)
}