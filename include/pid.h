#ifndef PID_H
#define PID_H

#include <functional>
#include <cmath>

/**
 * @brief PID Controller function
 * 
 */
/**
 * @brief PID Controller function
 * 
 */
class PID {
private:
    // Main parameters
    double p; 
    double i;
    double d;

    // extra parameters for stability
    double maxPower;    
    double minPower;    
    double factor;      
    double minErrThreshold;
    double slew;

    // variables that change throughout step
    double prevError;   // the previous error from last step function
    double prevOutput;  // the previous output from last step function
    double errorSum;    // Integral part of PID

public:
    
    // initialization function
    /**
     * @brief Construct a new PID object
     * 
     * @param p main parameter for P
     * @param i main parameter for I
     * @param d main parameter for D
     * @param minErrThreshold if the err becomes smaller than <0.1 for example, then we disable incrementing error sum (i.e no i in PID)
     * @param maxPower limit max power variable
     * @param minPower limit min power variable
     * @param factor the factor, from 0 - 1 will control the range of the PID value
     */
    PID (double p, double i, double d, double minErrThreshold=0, double maxPower=1, double minPower=0, double slew=1, double factor=1) : 
        p(p), i(i), d(d), maxPower(maxPower), minPower(minPower), factor(factor), minErrThreshold(minErrThreshold), slew(slew), prevError(0), prevOutput(0), errorSum(0) {} 

    // reset the PID variables
    void reset ();

    // set new factor (usually in the middle of a run)
    void setFactor (double newFactor);

    // step function
    double step (double error);
};

#endif