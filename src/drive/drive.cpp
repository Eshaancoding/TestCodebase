#include "drive.h"
#include "Console.h"
#include "Odom/Math.h"
#include "okapi/api/odometry/odomState.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include "parameters.h"
#include "odom/OdomCustom.h"
#include "PIDParams.h"

// basically we define a bunch of functions that just wraps around the moveToPoint function

void Drive::goForward (
    QLength distance,
    std::map<double, double> factorMap,
    std::map<double, std::function<void()>> callbackMap
) {
    // get starting position and then offset
    okapi::OdomState startingPos = OdomCustom::getPos();
    Point absolute = Math::findPointOffset(startingPos, distance);

    // convert from factor map to multiple of factor map cause not doing so is cringe
    double last_interest = 0;
    map<double, pair<double, double>> map;
    for (auto i : factorMap) {
        map[i.first] = {i.second, Heading_FACTOR}; 
        last_interest = i.second;
    }

    // wait... this is weird we are activating heading too!
    // the reason why is because say that the robot swerves a little bit, we could use the heading at the same time as the distance to correct it a little bit.

    // we have to disable the heading somewhere at the end BECAUSE angle point becomes larger and larger as it grows closer to the point!
    double disablePoint = DISABLEPOINT; 
    if (map.find(disablePoint) == map.end()) { // not found in map
        map[disablePoint] = {last_interest, 0}; // completely disables heading! only allows distance
    }

    move(absolute, false, COURSE_CORRECTION, true, true, map, callbackMap);
}


void Drive::goBackward (
    QLength distance,
    std::map<double, double> factorMap,
    std::map<double, std::function<void()>> callbackMap
) {
    goForward(-distance, factorMap, callbackMap);
}

void Drive::turnRight (
    QAngle ang,
    std::map<double, double> factorMap,
    std::map<double, std::function<void()>> callbackMap
) {
    okapi::OdomState startingPos = OdomCustom::getPos();
    Point absolute = Math::findPointOffset({startingPos.x, startingPos.y, startingPos.theta + ang}, 20_tile);

    // convert from factor map to multiple of factor map cause thats cringe
    map<double, pair<double, double>> map;
    for (auto i : factorMap) {
        map[i.first] = {0, i.second};
    }

    move(absolute, false, true, false, true, map, callbackMap);
}

void Drive::turnLeft (
    QAngle ang,
    std::map<double, double> factorMap,
    std::map<double, std::function<void()>> callbackMap
) {
    turnRight(-ang, factorMap, callbackMap);
}

void Drive::faceToPoint (
    Point point, 
    bool isRelative,
    std::map<double, double> factorMap,
    std::map<double, std::function<void()>> callbackMap
) {
    map<double, pair<double, double>> map;
    for (auto i : factorMap) {
        map[i.first] = {Distance_FACTOR, i.second};
    }

    move(point, isRelative, true, false, true, map, callbackMap);
}

void Drive::goToPoint (
    Point point,
    bool isRelative,
    bool isCC,
    std::map<double, double> factorMap,
    std::map<double, std::function<void()>> callbackMap
) {
    // convert from factor map to multiple of factor map cause not doing so is cringe
    map<double, pair<double, double>> map;
    for (auto i : factorMap) {
        map[i.first] = {i.second, Heading_FACTOR}; 
    }

    // wait... this is weird we are activating heading too!
    // the reason why is because say that the robot swerves a little bit, we could use the heading at the same time as the distance to correct it a little bit.

    // we have to disable the heading somewhere at the end BECAUSE angle point becomes larger and larger as it grows closer to the point!
    double disablePoint = DISABLEPOINT; 
    if (map.find(disablePoint) == map.end()) { // not found in map
        map[disablePoint] = {1, 0}; // completely disables heading! only allows distance
    }

    move(point, isRelative, COURSE_CORRECTION, true, !isCC, map, callbackMap);   
}