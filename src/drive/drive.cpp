#include "drive.h"
#include "Console.h"
#include "Odom/Math.h"
#include "okapi/api/odometry/odomState.hpp"
#include "okapi/api/units/QAcceleration.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QSpeed.hpp"
#include "parameters.h"
#include "odom/OdomArc.h"
#include "odom/OdomCustom.h"

// basically we define a bunch of functions that just wraps around the faceToPoint s& move function

void Drive::goForward (
    QLength distance,
    optional<QSpeed> vel,
    optional<QAcceleration> accel,
    optional<QTime> timeout,
    optional<QLength> end_tolerance
) {
    // get starting position and then offset
    okapi::OdomState startingPos = OdomArc::getPos();
    Point absolute = Math::findPointOffset(startingPos, distance);
    move(
        {
            DrivePoint({startingPos.x, startingPos.y}, nullopt, vel),
            DrivePoint(absolute)
        },
        end_tolerance,
        accel,
        timeout,
        end_tolerance
    );
}


void Drive::goBackward (
    QLength distance,
    optional<QSpeed> vel,
    optional<QAcceleration> accel,
    optional<QTime> timeout,
    optional<QLength> end_tolerance
) {
    goForward(-distance, vel, accel, timeout, end_tolerance);
}

void Drive::turnRight (
    QAngle ang,
    optional<QAngularSpeed> vel,
    optional<QAngularAcceleration> accel,
    optional<double> kp,
    optional<QTime> timeout,
    optional<QAngle> end_tolerance
) {
    okapi::OdomState startingPos = OdomArc::getPos();
    Point absolute = Math::findPointOffset({startingPos.x, startingPos.y, startingPos.theta + ang}, 20_tile);

    faceToPoint(
        absolute,
        vel,
        accel,
        kp,
        timeout,
        end_tolerance
    );
}

void Drive::turnLeft (
    QAngle ang,
    optional<QAngularSpeed> vel,
    optional<QAngularAcceleration> accel,
    optional<double> kp,
    optional<QTime> timeout,
    optional<QAngle> end_tolerance
) {
    turnRight(-ang, vel, accel, kp, timeout, end_tolerance);
}