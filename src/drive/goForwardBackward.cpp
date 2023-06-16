#include "drive.h"
#include "parameters.h"
#include "OdomMath.h"

void Drive::goForward(
    QLength distance, 
    std::map<double, double> factorMap, 
    std::map<double, std::function<void()>> callbackMap
) {

    // ========= Initial Variable Declaration ========

    DistancePID.reset();  // reset distance PID
    auto startingPos = odometery.getPos(); // get initial position
    auto targetPos = Math::findPointOffset(startingPos, distance);
    auto start = pros::millis(); // for recording the time ellapse
    QLength err = Math::distance(startingPos, targetPos); // should be close to distance
    QLength origErr = err;
    
    while (true) { // whoaaa while true loop that's dangerous :O

        // ========= Handle Factor and Callback Map ========

        // determine what point of the path we are on. 
        double percentChange = abs((origErr.convert(okapi::inch) - err.convert(okapi::inch)) / origErr.convert(okapi::inch));

        // go through factor map and set factor map if necessary
        for (auto itr = factorMap.begin(); itr != factorMap.end(); itr++) {
            if (itr->first > percentChange) {
                DistancePID.setFactor(itr->second);
                factorMap.erase(itr);
                break;
            }
        }

        // go through callback map and call if necessary
        for (auto itr = callbackMap.begin(); itr != callbackMap.end(); itr++) {
            if (itr->first > percentChange) {
                itr->second();
                callbackMap.erase(itr);
                break;
            }
        }

        // ================ Step through PID ==============

        double power = DistancePID.step(err.convert(okapi::inch));
        leftMotorGroup.moveVelocity(power * 128);    // maybe use voltage? 
        rightMotorGroup.moveVelocity(power * 128);   // maybe use voltage?
        err = Math::distance(odometery.getPos(), targetPos);
        
        // ================ Check whether we should stop ==============
        if (okapi::abs(err) < distanceTol) break; 
        if ((pros::millis() - start) >= timeTol.convert(okapi::millisecond)) break;
    }
}

void Drive::goBackward(
    QLength distance, 
    std::map<double, double> factorMap, 
    std::map<double, std::function<void()>> callbackMap
) {
    goForward(-distance, factorMap, callbackMap); // goBackward function is mainly because of the name. Other than that, it's pretty much like goForward.
}