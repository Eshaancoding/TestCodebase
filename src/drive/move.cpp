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
    std::map<double, pair<double, double>> factorMap,
    std::map<double, std::function<void()>> callbackMap
) {
    // ========= Initial Variable Declaration =========  

    // reset PID
    DistancePID.reset();
    HeadingPID.reset();

    // get starting position
    okapi::OdomState startingPos;
    if (ENABLE_ODOMSIM) startingPos = simulation.getPos();
    else                startingPos = odometery.getPos();

    // get target position and distance/angle error 
    auto targetPos = isRelative ? add(startingPos, point) : point;
    QLength distErr = Math::distance(startingPos, targetPos);

    QAngle angleErr = Math::anglePoint(startingPos, targetPos, distanceActivated);

    // record original distance and angle error as well as time
    auto start = pros::millis();
    QLength origDistErr = distErr;
    QAngle origAngleErr = angleErr;

    // initialize Moving Average (for determining stop)
    MovingAverage distanceAvg (Distance_N);
    MovingAverage headingAvg (Heading_N);
    distanceAvg.step(distErr.convert(inch));
    headingAvg.step(angleErr.convert(radian));

    // record previous factors + clear line
    double prevDistanceFact = DistancePID.getFactor();
    double prevHeadingFact = HeadingPID.getFactor();

    if (ODOM_DEBUG) Console::printBrain(4, "");

    // =================== Main loop ==================

    while (true) { 

        // determine which percent change (used for callback map and factor mapto use; by default distance
        double percentChange;
        if (distanceActivated) 
            percentChange = abs(distErr.convert(inch)-origDistErr.convert(inch))/(abs(origDistErr.convert(inch)));
        else                   
            percentChange = abs(angleErr.convert(radian)-origAngleErr.convert(radian))/(abs(origAngleErr.convert(radian)));

        // go through factor map
        for (auto itr = factorMap.begin(); itr != factorMap.end(); itr++) {
            if (itr->first < percentChange && percentChange <= 1) {
                if (distanceActivated) DistancePID.setFactor(get<0>(itr->second));
                if (headingActivated) HeadingPID.setFactor(get<1>(itr->second));

                /// TEST 
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

        // add to sim
        if (ENABLE_ODOMSIM) simulation.step(distancePower, headingPower);
        else                Drive::moveArcade(distancePower, -headingPower);
        
        // update error
        okapi::OdomState newPos;
        if (ENABLE_ODOMSIM) newPos = simulation.getPos();
        else                newPos = odometery.getPos();
        distErr = Math::distance(newPos, targetPos);
        angleErr = Math::anglePoint(newPos, targetPos, distanceActivated);

        // add to moving average function 
        distanceAvg.step(distErr.convert(inch));
        headingAvg.step(angleErr.convert(radian));

        // debug if we need to 
        if (ODOM_DEBUG) {
            Console::printBrain(0, "Dist err: %.3f in Ang err: %.3f deg", distErr.convert(inch), angleErr.convert(degree));
            Console::printBrain(1, "D: %.3f H: %.3f", distancePower, headingPower);
            Console::printBrain(2, targetPos, "Target Pos");
            Console::printBrain(3, simulation.getPos(), "Pos");
        }

        // check on if we should stop or not
        if (
            ((!distanceActivated || DistancePID.getFactor() == 0) || abs(distanceAvg.value()) <= distanceTol.convert(inch)) &&
            ((!headingActivated || HeadingPID.getFactor() == 0) || abs(headingAvg.value()) <= angleTol.convert(radian))
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

    if (!ENABLE_ODOMSIM) Drive::moveArcade(0, 0);
}