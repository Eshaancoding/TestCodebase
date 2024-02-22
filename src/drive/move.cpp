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
#include "odom/OdomCustom.h"
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
    okapi::OdomState startingPos = OdomCustom::getPos();

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
    double prevDistanceFact = DistancePID.getFactor(); // get the previous factor for setting at the end
    double prevHeadingFact = HeadingPID.getFactor();   // get the previous factor for setting at the end
    if (ODOM_DEBUG) Console::printBrain(4, ""); // clear line

    // =================== Main loop ==================

    while (true) { 

        // determine which percent change (used for callback map and factor map to use; by default uses distance
        double percentChange;
        if (distanceActivated) 
            percentChange = abs(distErr.convert(inch)-origDistErr.convert(inch))/(abs(origDistErr.convert(inch)));
        else                   
            percentChange = abs(angleErr.convert(radian)-origAngleErr.convert(radian))/(abs(origAngleErr.convert(radian)));

        // go through factor map; commented because you have weird code for factors
        for (auto itr = factorMap.begin(); itr != factorMap.end(); itr++) {
            if (itr->first < percentChange && percentChange <= 1) {
                if (distanceActivated) DistancePID.setFactor(get<0>(itr->second));
                if (headingActivated) HeadingPID.setFactor(get<1>(itr->second));

                /// SKILL 
                if (ODOM_DEBUG)
                    Console::printBrain(4, "Setting D Factor: %.3f and H Factor: %.3f at %.3f", get<0>(itr->second), get<1>(itr->second), percentChange);

                factorMap.erase(itr);
                break;
            }
        }

        // go through callback map
        for (auto itr = callbackMap.begin(); itr != callbackMap.end(); itr++) {
            if (itr->first < percentChange && percentChange <= 1) {
                itr->second();

                if (ODOM_DEBUG)
                    Console::printBrain(4, "Running function at %.3f", percentChange);

                callbackMap.erase(itr);
                break;
            }
        }

        // step through PIDOdomMath
        double distancePower = 0;
        double headingPower  = 0;
        if (distanceActivated) distancePower = DistancePID.step(distErr.convert(inch));
        if (headingActivated)  headingPower  = HeadingPID.step(angleErr.convert(radian));

        if (headingActivated && distanceActivated && setFactorCC) 
            headingPower *= courseCorrectionFactor;

        // Actually drive
        Drive::moveArcade(distancePower, headingPower);
        
        // update error
        okapi::OdomState newPos = OdomCustom::getPos();
        distErr = Math::distance(newPos, targetPos);
        if (distErr >= LOOKAHEAD_DIST) distErr = LOOKAHEAD_DIST;
        if (distErr <= -LOOKAHEAD_DIST) distErr = -LOOKAHEAD_DIST;
        angleErr = Math::anglePoint(newPos, targetPos, distanceActivated);

        // debug if we need to 
        if (ODOM_DEBUG) {
            Console::printBrain(0, "Dist err: %.3f in Ang err: %.3f deg", distErr.convert(inch), angleErr.convert(degree));
            Console::printBrain(1, "D: %.3f H: %.3f", distancePower, headingPower);
            Console::printBrain(2, targetPos, "Target Pos");
            Console::printBrain(3, OdomCustom::getPos(), "Pos");
        }

        // check on if we should stop or not
        if (
            ((!distanceActivated || DistancePID.getFactor() == 0) || abs(distErr.convert(inch)) <= distanceTol.convert(inch)) &&
            ((!headingActivated || HeadingPID.getFactor() == 0) || abs(angleErr.convert(radian)) <= angleTol.convert(radian))
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

    // set previous factor for PID factor
    HeadingPID.setFactor(prevHeadingFact);
    DistancePID.setFactor(prevDistanceFact);

    Drive::moveArcade(0, 0); // reset!

    pros::delay(100);

}