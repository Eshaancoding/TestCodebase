#ifndef DRIVE_H
#define DRIVE_H

#include "Console.h"
#include "parameters.h"
#include "main.h"
#include <map>
#include "MovingAverage.h"

class Drive {
private:
    QLength distanceTol = DISTANCE_TOLERANCE;
    QAngle angleTol = ANGLE_TOLERANCE;
    QTime timeTol = TIME_TOLERANCE;

public:
    bool drive = false;
    /**
     * @brief move arcade
     * 
     * @param distance the distance (forward/backward)
     * @param heading  the heading (left/right)  ** + counter clockwise **
     */
    void moveArcade (double distance, double heading) {
        distance *= 128; heading *= 128;
        leftMotorGroup.moveVelocity(distance - heading);    // maybe use voltage? 
        rightMotorGroup.moveVelocity(distance + heading);   // maybe use voltage?
    }

    /**
     * @brief move arcade
     * 
     * @param distance the distance (forward/backward)
     * @param heading  the heading (left/right)  ** + counter clockwise **
     */
    void moveTank (double left, double right) {
        left *= 128; right *= 128;
        leftMotorGroup.moveVelocity(left);     // maybe use voltage? 
        rightMotorGroup.moveVelocity(right);   // maybe use voltage?
    }

    /**
     * @brief Go forward for x distance
     * 
     * @param distance the distance required to travel forward
     * @param factorMap the factor map used to slow down robot in the middle of run 
     * @param callbackMap the map used to execute functions in the middle of the run (ex: running intake at 50% of run)
     */
    void goForward (
        QLength distance,
        std::map<double, double> factorMap={},
        std::map<double, std::function<void()>> callbackMap={}
    );

    /**
     * @brief go backward for x distance
     * 
     * @param distance distance required to travel backward
     * @param factorMap the factor map used to slow down robot in the middle of run 
     * @param callbackMap the map used to execute functions in the middle of the run (ex: running intake at 50% of run)
     */
    void goBackward (
        QLength distance,
        std::map<double, double> factorMap={},
        std::map<double, std::function<void()>> callbackMap={}
    );

    /**
     * @brief turn the robot left (point turn)
     * 
     * @param ang the specified angle to turn right
     * @param factorMap the factor map used to slow down robot in the middle of run 
     * @param callbackMap the map used to execute functions in the middle of the run (ex: running intake at 50% of run)
     */
    void turnLeft (
        QAngle ang,
        std::map<double, double> factorMap={},
        std::map<double, std::function<void()>> callbackMap={}
    );

    /**
     * @brief turn the robot right (point turn)
     * 
     * @param ang the specified angle to turn right
     * @param factorMap the factor map used to slow down robot in the middle of run 
     * @param callbackMap the map used to execute functions in the middle of the run (ex: running intake at 50% of run)
     */
    void turnRight (
        QAngle ang,
        std::map<double, double> factorMap={},
        std::map<double, std::function<void()>> callbackMap={}
    );

    /**
     * @brief Set the Tolerance Params object
     * 
     * @param distanceTolP distance tolerance (set null opt if no change)
     * @param angleTolP   angle tolerance (set null opt if no change)
     * @param timeTolP    time tolerance (set null opt if no change)
     */
    void setToleranceParams (
        std::optional<QLength> distanceTolP=std::nullopt,
        std::optional<QAngle> angleTolP=std::nullopt,
        std::optional<QTime> timeTolP=std::nullopt
    );

    /**
     * @brief resets tolerance params
    */
    void resetToleranceParams ();
};

#endif