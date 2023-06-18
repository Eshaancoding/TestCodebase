#ifndef MOVINGAVERAGE
#define MOVINGAVERAGE
#include <vector>
#include <numeric>
#include <cmath>


/**
 * HEY WHY DONT YOU USE THE OKAPI LIB HM?
 * yeah but that's what NERDS do I am not a nerd I am just a herd :) 
 */

class MovingAverage {
private:
    std::vector<double> avgs; 
    int n;
public:
    MovingAverage (int n) : n(n) {};

    void step (double val) {
        avgs.push_back(std::abs(val));
        if (avgs.size() > n) avgs.erase(avgs.begin());
    }

    double value () { return std::reduce(avgs.begin(), avgs.end()) / avgs.size(); };

};

#endif