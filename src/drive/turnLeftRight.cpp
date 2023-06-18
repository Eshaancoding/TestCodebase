#include "drive.h"
#include "okapi/api/units/QAngle.hpp"
#include "parameters.h"
#include "odom/OdomMath.h"

void Drive::turnRight(
    QAngle ang, 
    std::map<double, double> factorMap, 
    std::map<double, std::function<void()>> callbackMap
) {

    // ========= Initial Variable Declaration ========

    HeadingPID.reset();  // reset distance PID
    okapi::OdomState startingPos;
    if (ENABLE_ODOMSIM) 
        startingPos = simulation.getPos();
    else
        startingPos = odometery.getPos();
    auto targetAngle = startingPos.theta + ang;
    auto start = pros::millis(); // for recording the time ellapse
    QAngle err = ang;
    QAngle origErr = err;
    
    while (true) {

        // ========= Handle Factor and Callback Map ========

        // determine what point of the path we are on. 
        double percentChange = abs((origErr.convert(okapi::degree) - err.convert(okapi::degree)) / origErr.convert(okapi::degree));

        // go through factor map and set factor map if necessary
        for (auto itr = factorMap.begin(); itr != factorMap.end(); itr++) {
            if (itr->first > percentChange) {
                HeadingPID.setFactor(itr->second);
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

        double power = HeadingPID.step(Math::restrictAngle180(err).convert(okapi::radian));
        if (ENABLE_ODOMSIM) {
            simulation.step(0, power);
            err = targetAngle - simulation.getPos().theta;
        }
        else {
            Drive::moveArcade(0, power);
            err = targetAngle - odometery.getPos().theta;
        }
        
        // ================ Check whether we should stop ==============
        if (okapi::abs(err) < angleTol) break; 
        if ((pros::millis() - start) >= timeTol.convert(okapi::millisecond)) break;

        // delay a little bit
        pros::delay(DELAYITER.convert(okapi::millisecond)); 
    }
}

void Drive::turnLeft(
    QAngle ang, 
    std::map<double, double> factorMap, 
    std::map<double, std::function<void()>> callbackMap
) {
    turnRight(-ang, factorMap, callbackMap);
}