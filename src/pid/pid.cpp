#include "pid.h"
#include <algorithm>

// reset variables that change throughout step
void PID :: reset () { 
    prevError = 0; 
    prevOutput = 0;
    errorSum = 0;
}

double PID :: step (double error) {
    // increase error sum if it doesn't go over max error sum threshold
    if (std::abs(error) > minErrThreshold) errorSum += error; 
    else errorSum = 0;

    // calculate the derivative (after all its just the slope) 
    double dir = error - prevError;

    // calculate output
    double output = (error * p) + (errorSum * i) + (dir * d);

    // apply factor
    output *= factor;

    // clamp between maxPower and minPower and also provide slew
    // we do this by converting to just positive number and then after computation set it to negative or positive

    output = std::clamp(
        std::abs(output), 
        std::max(minPower, std::abs(prevOutput) - slew), 
        std::min(maxPower, std::abs(prevOutput) + slew)
    ) * (output < 0 ? -1 : 1);

    // set all prev variables to current
    prevError = error;
    prevOutput = output;

    return output; 
}

void PID :: setFactor(double newFactor) {
    factor = newFactor;
}