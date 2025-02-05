#include "motionProfiling.h"

MotionProfiling :: MotionProfiling (vector<DrivePoint> points) {
     
}

double Square::y (double x) {
    if (x < min || x > max) return 0.0;
    return h;
}

double Square::area (double x) {
    if (x < min || x > max) return 0.0;
    return (x - min) * h;
}

bool Square::in_bounds (double x) { return x >= min && x <= max; }

double Triangle::y (double x) {
    if (x < min || x > max) return 0.0;
    double xbar = (min + max) / 2;
    double ybar = (y2 + y1) / 2;
    double slope = (y2 - y1) / (max - min);
    return slope * (x - xbar) + ybar;
}

double Triangle::area (double x) {
    if (x < min || x > max) return 0.0;
    double min_y = y1 < y2 ? y1 : y2;
    return min_y * (x - min) + (0.5 * (x - min) * abs(y2 - y1));
}

bool Triangle::in_bounds (double x) { return x >= min && x <= max; }