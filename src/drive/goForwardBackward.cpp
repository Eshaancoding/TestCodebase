#include "BrainScreen/Console.h"
#include "MovingAverage.h"
#include "drive.h"
#include "okapi/api/odometry/odomState.hpp"
#include "okapi/api/units/QTime.hpp"
#include "parameters.h"
#include "Odom/OdomMath.h"

void Drive::goForward(
    QLength distance, 
    std::map<double, double> factorMap, 
    std::map<double, std::function<void()>> callbackMap
) {

    // ========= Initial Variable Declaration ========

    DistancePID.reset();  // reset distance PID

    okapi::OdomState startingPos;
    if (ENABLE_ODOMSIM) 
        startingPos = simulation.getPos(); // get initial position
    else
        startingPos = odometery.getPos(); // get initial position

    auto targetPos = Math::findPointOffset(startingPos, distance);
    auto start = pros::millis(); // for recording the time ellapse
    QLength err = Math::distance(startingPos, targetPos); // should be close to distance
    QLength origErr = err;

    MovingAverage avg (Distance_N);
    avg.step(err.convert(inch));
    
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
        if (ENABLE_ODOMSIM) {
            simulation.step(power, 0);
            err = Math::distance(simulation.getPos(), targetPos);
        } 
        else {
            Drive::moveArcade(power, 0);
            err = Math::distance(odometery.getPos(), targetPos);
        }
        avg.step(err.convert(inch));

        Console::printBrain(0, power, "Power");
        Console::printBrain(1, err, "Error");
        Console::printBrain(2, simulation.getPos(), "Position: ");
        Console::printBrain(3, targetPos, "Target Pos: ");
        Console::printBrain(4, avg.value(), "Moving average out: ");
        
        // ================ Check whether we should stop ==============
        if (abs(avg.value()) <= distanceTol.convert(okapi::inch)) {
            Console::printBrain(5, "We stopped cause of err tolerance.");
            break; 
        }
        if ((pros::millis() - start) >= timeTol.convert(okapi::millisecond)) {
            Console::printBrain(5, "We stopped cause of time.");
            break;
        }

        pros::delay(DELAYITER.convert(okapi::millisecond)); 
    }
}

void Drive::goBackward(
    QLength distance, 
    std::map<double, double> factorMap, 
    std::map<double, std::function<void()>> callbackMap
) {
    goForward(-distance, factorMap, callbackMap); // goBackward function is mainly because of the name. Other than that, it's pretty much like goForward.
}