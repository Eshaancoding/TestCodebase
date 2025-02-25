#include "Console.h"
#include "MovingAverage.h"
#include "drive.h"
#include "Odom/Math.h"
#include "okapi/api/odometry/odomState.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QTime.hpp"
#include "parameters.h"
#include "pros/adi.h"
#include "effectors.h"
#include "odom/OdomArc.h"
#include "PIDParams.h"

Point add (okapi::OdomState orig, Point p) {
    p.x += orig.x;
    p.y += orig.y;
    return p; 
}

void Drive::move (
    Point point, 
    bool isRelative,
    bool headingActivated, 
    bool distanceActivated,
    bool setFactorCC,
    std::map<double, pair<double, double>> factorMap,
    std::map<double, std::function<void()>> callbackMap
) {
    // ========= Initial Variable Declaration =========  

    // reset PID
    DistancePID.reset();
    HeadingPID.reset();

    // get starting position
    okapi::OdomState startingPos = OdomArc::getPos();

    // get target position and distance/angle error 
    auto targetPos = isRelative ? add(startingPos, point) : point;
    QLength distErr = Math::distance(startingPos, targetPos);
    if (distErr >= LOOKAHEAD_DIST) distErr = LOOKAHEAD_DIST;
    if (distErr <= -LOOKAHEAD_DIST) distErr = -LOOKAHEAD_DIST;

    QAngle angleErr = Math::anglePoint(startingPos, targetPos, distanceActivated);

    // record original distance and angle error as well as time
    auto start = pros::millis();
    QLength origDistErr = distErr;
    QAngle origAngleErr = angleErr;

    // record previous factors 
    if (ODOM_DEBUG) Console::printBrain(4, ""); // clear line

    double heading_factor = 1;
    double distance_factor = 1;

    // =================== Main loop ==================
    int iteration = 0;

    while (true) { 
        iteration++;
        // determine which percent change (used for callback map and factor map to use; by default uses distance
        double percentChange;
        if (distanceActivated) 
            percentChange = abs(Math::distance(OdomArc::getPos(), targetPos).convert(inch)-origDistErr.convert(inch))/(abs(origDistErr.convert(inch)));
        else                   
            percentChange = abs(angleErr.convert(radian)-origAngleErr.convert(radian))/(abs(origAngleErr.convert(radian)));

        printf("Percentage change: %f\n", percentChange);

        // go through factor map; commented because you have weird code for factors
        for (auto itr = factorMap.begin(); itr != factorMap.end(); itr++) {
            if (itr->first < percentChange && percentChange <= 1) {
                distance_factor = get<0>(itr->second);
                heading_factor = get<1>(itr->second);

                printf("Heading factor: %f\n", heading_factor);
                printf("Distance factor: %f\n", distance_factor);
                printf("Percent change %f with i: %f \n", percentChange, (float)itr->first);

                /// SKILL 
                if (ODOM_DEBUG)
                    Console::printBrain(4, "Setting D Factor: %.3f and H Factor: %.3f at %.3f", get<0>(itr->second), get<1>(itr->second), percentChange);

                factorMap.erase(itr);
                break;
            }
        }

        // go through callback map
        for (auto itr = callbackMap.begin(); itr != callbackMap.end(); itr++) {
            if (itr->first <= percentChange && percentChange <= 1) {
                itr->second();
                
                printf("called func\n");

                if (ODOM_DEBUG)
                    Console::printBrain(4, "Running function at %.3f", percentChange);

                //callbackMap.erase(itr);
                break;
            }
        }

        // step through PIDOdomMath
        double distancePower = 0;
        double headingPower  = 0;
        if (distanceActivated) distancePower = DistancePID.step(distErr.convert(inch));
        if (headingActivated)  headingPower  = HeadingPID.step(angleErr.convert(radian));

        if (headingActivated && distanceActivated && setFactorCC) 
            headingPower *= (distErr < 4_in) ? 0 : courseCorrectionFactor;

        // Actually drive
        if (iteration % 3 == 0) {
            printf("power distnace: %f ", distancePower * distance_factor * (distanceActivated ? 1 : 0));
            printf("raw power: %f\n", distancePower);
        }
        Drive::moveArcade(
            distancePower * distance_factor * (distanceActivated ? 1 : 0), 
            headingPower * heading_factor * (headingActivated ? 1 : 0)
        );
        
        // update error
        okapi::OdomState newPos = OdomArc::getPos();
        distErr = Math::distance(newPos, targetPos);
        if (distErr >= LOOKAHEAD_DIST) distErr = LOOKAHEAD_DIST;
        if (distErr <= -LOOKAHEAD_DIST) distErr = -LOOKAHEAD_DIST;
        angleErr = Math::anglePoint(newPos, targetPos, distanceActivated);

        // debug if we need to 
        if (ODOM_DEBUG) {
            Console::printBrain(0, "Dist err: %.3f in Ang err: %.3f deg", distErr.convert(inch), angleErr.convert(degree));
            Console::printBrain(1, "D: %.3f H: %.3f", distancePower, headingPower);
            Console::printBrain(2, targetPos, "Target Pos");
            Console::printBrain(3, OdomArc::getPos(), "Pos");
        }

        // check on if we should stop or not
        if (
            ((!distanceActivated || distance_factor == 0) || abs(distErr.convert(inch)) <= distanceTol.convert(inch)) &&
            ((!headingActivated || heading_factor == 0) || abs(angleErr.convert(radian)) <= angleTol.convert(radian))
        ) {
            if (ODOM_DEBUG) Console::printBrain(4, "Stopped due to heading/distance threshold reached.");
            break;
        }
        if ((pros::millis() - start) >= timeTol.convert(okapi::millisecond)) {
            if (ODOM_DEBUG) Console::printBrain(4, "Stopped because exceeded time limit");
            break;
        }

        pros::delay(DELAYITER.convert(okapi::millisecond));
    }

    Drive::moveArcade(0, 0); // reset!

    pros::delay(100);

}

void Drive::setToleranceParams(std::optional<QTime> timeTolP, std::optional<QLength> distanceTolP, std::optional<QAngle> angleTolP, std::optional<double> ccFactor ) {
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