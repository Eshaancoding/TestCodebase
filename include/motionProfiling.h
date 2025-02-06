#ifndef MOTION_PROFILING
#define MOTION_PROFILING

#include "drive.h"
#include "okapi/api/units/QAcceleration.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QSpeed.hpp"
#include "okapi/api/units/QTime.hpp"


class PathSegment {
public:
    QSpeed speed;
    QTime time;    

    PathSegment(
        QSpeed speed,
        QTime time
    ) : 
        speed(speed),
        time(time)
    {};
};

class MotionProfiling {
private: 
    vector<PathSegment> shapes;
    QAcceleration acc;
    QTime total_time;

public:
    MotionProfiling (vector<DrivePoint> points, QAcceleration acc);
    QSpeed vel (QTime s);
    QLength dist (QTime s);
};

#endif

/*


double MotionProfiling :: vel (double s) {
    // check if we are in acceleration or deceleration
    double speed_beginning = this->shapes[0].speed;
    double speed_end = this->shapes[this->shapes.size() - 1].speed;

    // acceleration
    if (s <= speed_beginning / acc) {
        return acc * s;
    } 

    // deacceleration
    auto decel_start = this->total_time - (speed_end / acc);
    if (s >= decel_start && s <= this->total_time) {
        return speed_end - (acc * (s - decel_start));
    }

    // check whether we are accelerating/decelerrating in between movements
    double t = 0;
    for (int i = 0; i < this->shapes.size() - 1; i++) {
        auto first_shape = this->shapes[i];
        auto second_shape = this->shapes[i+1];
        double avg_y = (first_shape.speed + second_shape.speed) / 2.0;

        t += first_shape.time;
        double tol = abs( (second_shape.speed - first_shape.speed) / (2 * acc) ); 

        if (s >= t - tol && s <= t + tol) {
            std::cout << "In range: " << t - tol << " to " << t + tol << " | v: " << s << std::endl;
            double acc_line = (second_shape.speed > first_shape.speed) ? acc : -acc;
            return (acc_line * (s - t) + avg_y);
        }
    }

    // else, we are in cruise
    t = 0;
    for (auto sh : this->shapes) {
        t += sh.time;
        if (s <= t) {
            std::cout << "In cruise: " << s << " < " << t << " | v: " << sh.speed << std::endl;
            return sh.speed;
        };
    }
    
    return 0;
}
*/