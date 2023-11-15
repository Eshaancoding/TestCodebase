#include "drive.h"
#include "parameters.h"

void Drive::setToleranceParams(std::optional<QLength> distanceTolP, std::optional<QAngle> angleTolP, std::optional<QTime> timeTolP) {
    if (distanceTolP)
        distanceTol = *distanceTolP;

    if (angleTolP) 
        angleTol = *angleTolP;

    if (timeTolP) {
        timeTol = *timeTolP;
        Console::printBrain(7, timeTol.convert(okapi::millisecond), "milli sec time tol set");
    }
}

void Drive::resetToleranceParams () {
    distanceTol = DISTANCE_TOLERANCE; 
    angleTol = ANGLE_TOLERANCE;
    timeTol = TIME_TOLERANCE;
}