#include "drive.h"
#include "Console.h"
#include "Odom/Math.h"
#include "okapi/api/odometry/odomState.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"

// basically we define a bunch of functions that just wraps around the moveToPoint function

void Drive::goForward (
    QLength distance,
    std::map<double, double> factorMap,
    std::map<double, std::function<void()>> callbackMap
) {
    // get starting position and then offset
    okapi::OdomState startingPos;
    if (ENABLE_ODOMSIM) startingPos = simulation.getPos();
    else                startingPos = odometery.getPos();
    Point absolute = Math::findPointOffset(startingPos, distance);

    // convert from factor map to multiple of factor map cause not doing so is cringe
    map<double, pair<double, double>> map;
    for (auto i : factorMap) {
        map[i.first] = {i.second, 1}; 
    }

    // wait... this is weird we are activating heading too!
    // the reason why is because say that the robot swerves a little bit, we could use the heading at the same time as the distance to correct it a little bit.

    // we have to disable the heading somewhere at the end BECAUSE angle point becomes larger and larger as it grows closer to the point!
    double disablePoint = DISABLEPOINT; 
    if (map.find(disablePoint) == map.end()) { // not found in map
        map[disablePoint] = {1, 0}; // completely disables heading! only allows distance
    }

    move(absolute, false, true, true, map, callbackMap);
}


void Drive::goBackward (
    QLength distance,
    std::map<double, double> factorMap,
    std::map<double, std::function<void()>> callbackMap
) {
    goForward(-distance, factorMap, callbackMap);
}

void Drive::turnLeft (
    QAngle ang,
    std::map<double, double> factorMap,
    std::map<double, std::function<void()>> callbackMap
) {
    okapi::OdomState startingPos;
    if (ENABLE_ODOMSIM) startingPos = simulation.getPos();
    else                startingPos = odometery.getPos();
    Point absolute = Math::findPointOffset({startingPos.x, startingPos.y, startingPos.theta + ang}, 1_in);

    // convert from factor map to multiple of factor map cause thats cringe
    map<double, pair<double, double>> map;
    for (auto i : factorMap) {
        map[i.first] = {1, i.second};
    }

    move(absolute, false, true, false, map, callbackMap);
}

void Drive::turnRight (
    QAngle ang,
    std::map<double, double> factorMap,
    std::map<double, std::function<void()>> callbackMap
) {
    turnLeft(-ang, factorMap, callbackMap);
}

void Drive::faceToPoint (
    Point point, 
    bool isRelative,
    std::map<double, double> factorMap,
    std::map<double, std::function<void()>> callbackMap
) {
    map<double, pair<double, double>> map;
    for (auto i : factorMap) {
        map[i.first] = {1, i.second};
    }

    move(point, isRelative, true, false, map, callbackMap);
}

void Drive::goToPoint (
    Point point,
    bool isRelative,
    std::map<double, double> factorMap,
    std::map<double, std::function<void()>> callbackMap
) {
    // convert from factor map to multiple of factor map cause not doing so is cringe
    map<double, pair<double, double>> map;
    for (auto i : factorMap) {
        map[i.first] = {i.second, 1}; 
    }

    // wait... this is weird we are activating heading too!
    // the reason why is because say that the robot swerves a little bit, we could use the heading at the same time as the distance to correct it a little bit.

    // we have to disable the heading somewhere at the end BECAUSE angle point becomes larger and larger as it grows closer to the point!
    double disablePoint = DISABLEPOINT; 
    if (map.find(disablePoint) == map.end()) { // not found in map
        map[disablePoint] = {1, 0}; // completely disables heading! only allows distance
    }

    move(point, isRelative, true, true, map, callbackMap);   
}