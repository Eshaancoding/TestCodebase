#include "main.h"
#include "okapi/api/odometry/point.hpp"
#include <map>
#include <tuple>
#include <vector>

class Bezier {
public:
    std::map<int, long> factorial_m;
    std::map<std::tuple<int, int>, float> m;
    std::vector<okapi::Point> points;

    std::vector<okapi::Point> curve;
    std::vector<okapi::Point> dCurve;
    std::vector<okapi::Point> ddCurve;
    
    int numPoints;
        
    long factorial (int n);
        
    double b (int n, int i, double u);
        
    Bezier (std::vector<okapi::Point> points, int numPoints) : 
        m({}), 
        points(points),
        numPoints(numPoints) 
    {};
    
    void calc ();
    
    std::vector<double> d ();
    std::vector<double> dd ();
    std::vector<double> k (); // curvature
};