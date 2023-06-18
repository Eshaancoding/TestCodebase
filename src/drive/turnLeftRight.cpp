#include "drive.h"
#include "okapi/api/odometry/odomMath.hpp"
#include "parameters.h"
#include "Odom/OdomMath.h"
#include "Console.h"

void Drive::turnRight(
    QAngle ang, 
    std::map<double, double> factorMap, 
    std::map<double, std::function<void()>> callbackMap
) {

    // ========= Initial Variable Declaration ========

    HeadingPID.reset();  // reset heading PID
    okapi::OdomState startingPos;
    if (ENABLE_ODOMSIM) 
        startingPos = simulation.getPos(); // get initial position
    else
        startingPos = odometery.getPos(); // get initial position

    auto targetAngle = OdomMath::constrainAngle180(startingPos.theta + ang);
    auto start = pros::millis(); // for recording the time ellapse
    QAngle err = ang;
    QAngle origErr = err;

    MovingAverage avg (Heading_N);
    avg.step(err.convert(radian));
    
    while (true) { // whoaaa while true loop that's dangerous :O

        // ========= Handle Factor and Callback Map ========

        // determine what point of the path we are on. 
        double percentChange = abs((origErr.convert(radian) - err.convert(radian)) / origErr.convert(radian));

        // go through factor map and set factor map if necessary
        for (auto itr = factorMap.begin(); itr != factorMap.end(); itr++) {
            if (itr->first < percentChange && percentChange <= 1) {
                HeadingPID.setFactor(itr->second);
                factorMap.erase(itr);
                break;
            }
        }

        // go through callback map and call if necessary
        for (auto itr = callbackMap.begin(); itr != callbackMap.end(); itr++) {
            if (itr->first < percentChange && percentChange <= 1) {
                itr->second();
                callbackMap.erase(itr);
                break;
            }
        }


        // ================ Step through PID ==============

        double power = HeadingPID.step(err.convert(radian));
        if (ENABLE_ODOMSIM) {
            simulation.step(0, power);
            err = targetAngle - simulation.getPos().theta;
        } 
        else {
            Drive::moveArcade(0, power);
            err = targetAngle - simulation.getPos().theta;
        }
        avg.step(err.convert(radian));
        
        // debug
        Console::printBrain(0, err, "Error");
        Console::printBrain(1, power, "Power");
        Console::printBrain(2, avg.value(), "MA Value");
        Console::printBrain(3, targetAngle, "Target Angle");
        Console::printBrain(4, simulation.getPos(), "Pos");
        
        // ================ Check whether we should stop ==============
        if (abs(avg.value()) <= angleTol.convert(okapi::radian)) break; 
        if ((pros::millis() - start) >= timeTol.convert(okapi::millisecond)) break;

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