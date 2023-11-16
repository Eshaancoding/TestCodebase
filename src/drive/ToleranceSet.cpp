#include "drive.h"
#include "parameters.h"

void Drive::setToleranceParams(std::optional<QLength> distanceTolP, std::optional<QAngle> angleTolP, std::optional<QTime> timeTolP) {
    if (distanceTolP)
        distanceTol = *distanceTolP;

    if (angleTolP) 
        angleTol = *angleTolP;

    if (timeTolP) {
        timeTol = *timeTolP;
    }
}

void Drive::resetToleranceParams () {
    distanceTol = DISTANCE_TOLERANCE; 
    angleTol = ANGLE_TOLERANCE;
    timeTol = TIME_TOLERANCE;
}