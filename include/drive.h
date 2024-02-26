#ifndef DRIVE_H
#define DRIVE_H

#include "Console.h"
#include "effectors.h"
#include "parameters.h"
#include "main.h"
#include <map>
#include "MovingAverage.h"
#include "Odom/Math.h"

class Path {
public:
    okapi::Point point;
    std::optional<std::function<void()>> callback;
    double headingFactor, distanceFactor;
    okapi::QLength lookaheadDistance;

    Path (
        okapi::Point p, 
        double headingF=1,
        double distanceF=1,
        okapi::QLength lookaheadDistance=0.3_tile, // has to be same 
        std::optional<std::function<void()>> func=std::nullopt
    )
        : point(p), 
        callback(func), 
        headingFactor(headingF), 
        distanceFactor(distanceF), 
        lookaheadDistance(lookaheadDistance) 
    {};
};

// I could make this a namespace idk why im making it a class
class Drive {
private:
    QLength distanceTol;
    QAngle angleTol;
    QTime timeTol;
    double courseCorrectionFactor;

    /**
     * @brief Essentially goes to the point but in general this houses the PID for both distance and heading
     * Every public function uses the move function under the hood.
     * The difference between this and the other functions is either    
     *      1. either heading/distance is deactivated, thus only allowing one type of movement (either going forward/backward or right/left)
     *      2. for movements that only go forward/backward, it will also enable the heading as a sort of correct just in case the robot swerves as the path goes on. The function (ex: goToPoint) also adds in a disable point in which it will automatically stop swerve correction (reason? explained in drive.cpp)
     * 
     * @param point  the point of interest (can be relative, i.e an offset)
     * @param isRelative if true, point offers as an offset rather than absolute position
     * @param headingActivated whether to activate heading (i.e enable robot turn left/right)
     * @param distanceActivated whether to activate distance (i.e enable robot to go forward/backward)
     * @param factorMap factormap. note that there's a pair, the first number is for the distance factor and second number in the pair is for the heading factor
     * @param callbackMap callbackm ap that is used to execute functions in the middle of the run. (ex: turning on an intake)
    **/
    void move (
        Point point, 
        bool isRelative=true,
        bool headingActivated=true, 
        bool distanceActivated=true,
        bool setFactorCC=true,
        std::map<double, pair<double, double>> factorMap={},
        std::map<double, std::function<void()>> callbackMap={}
    );

public:
    /**
     * @brief move arcade
     * 
     * @param distance the distance (forward/backward)
     * @param heading  the heading (left/right)  ** + clockwise **
     */
    void moveArcade (double distance, double heading);

    /**
     * @brief move arcade
     * 
     * @param distance the distance (forward/backward)
     * @param heading  the heading (left/right)  ** + counter clockwise **
     */
    void moveTank (double left, double right);

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
     * @brief faces to point that can be relative or absolute
     * 
     * @param point the point (or offset) to face the angle
     * @param isRelative is true, uses relative positioning if false then no
     * @param factorMap the factor map used to slow down robot in the middle of run 
     * @param callbackMap the map used to execute functions in the middle of the run (ex: running intake at 50% of run)
     */
    void faceToPoint (
        Point point,
        bool isRelative,
        std::map<double, double> factorMap={},
        std::map<double, std::function<void()>> callbackMap={}
    );

    /**
     * @brief goes to point that can be relative or absolute
     * 
     * @param point the point (or offset) to face the angle
     * @param isRelative is true, uses relative positioning if false then no
     * @param factorMap the factor map used to slow down robot in the middle of run 
     * @param callbackMap the map used to execute functions in the middle of the run (ex: running intake at 50% of run)
     */
    void goToPoint (
        Point point,
        bool isRelative,
        bool isCC=false,
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
        std::optional<QTime> timeTolP=std::nullopt,
        std::optional<double> ccFactor=std::nullopt
    );

    /**
     * @brief Pure pursuit (this is where we have a path object)
     * 
     * @param paths_initializer the paths to use in the pure pursuit algorithm
     * @param callbackTol the tolerance of the robot from the point to where to call the callback
     * @param endTol the tolerance that is used to stop the robot in its place
     * @param isReverse to check whether the robot is going in reverse or not
     * @param maxTime set the max time for the entire movement
     */
    void goPath (
        std::initializer_list<Path> paths_initializer,        
        QLength callbackTol=5_in,
        QLength endTol=2_in,
        bool isReverse=false,
        std::optional<QTime> maxTime=nullopt
    );
   

    /**
     * @brief resets tolerance params
    */
    void resetToleranceParams ();
};

#endif