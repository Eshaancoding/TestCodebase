#include "drive.h"
#include "parameters.h"
#include "PIDParams.h"

void Drive::setToleranceParams(std::optional<QLength> distanceTolP, std::optional<QAngle> angleTolP, std::optional<QTime> timeTolP, std::optional<double> ccFactor ) {
    if (distanceTolP)
        distanceTol = *distanceTolP;

    if (angleTolP) 
        angleTol = *angleTolP;

    if (timeTolP) {
        timeTol = *timeTolP;
    }
    if (ccFactor) {
        courseCorrectionFactor = *ccFactor;
    }
}

void Drive::resetToleranceParams () {
    distanceTol = DISTANCE_TOLERANCE; 
    angleTol = ANGLE_TOLERANCE;
    timeTol = TIME_TOLERANCE;
    courseCorrectionFactor = COURSE_CORRECTION_FACTOR;
}