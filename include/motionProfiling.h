#ifndef MOTION_PROFILING
#define MOTION_PROFILING

#include "drive.h"

class Shape {
public:
    virtual double y (double x) { return 0.0; };
    virtual double area (double x) { return 0.0; } ;
    virtual bool in_bounds (double x) { return false; };
};

class Square : public Shape {
public: 
    double h;
    double min;
    double max;

    Square (
        double h,
        double min,
        double max
    ) : 
        h(h),
        min(min),
        max(max)
    {};

    double y (double x) override;
    double area (double x) override;
    bool in_bounds (double x) override;
};

class Triangle : public Shape {
    double y1;
    double y2;
    double min;
    double max;

    Triangle (
        double y1,
        double y2,
        double min,
        double max
    ) : 
        y1(y1),
        y2(y2),
        min(min),
        max(max)
    {};

    double y (double x) override;
    double area (double x) override;
    bool in_bounds (double x) override;
};

class MotionProfiling {
public: 
    // safe pointers :D
    vector<unique_ptr<Shape>> shapes;

    MotionProfiling (vector<DrivePoint> points);
};

#endif