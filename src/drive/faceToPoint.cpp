#include "drive.h"
#include "Odom/Math.h"
#include "motionProfilingAngle.h"
#include "odom/OdomArc.h"

#include "okapi/api/odometry/odomState.hpp"
#include "okapi/api/units/QAcceleration.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QSpeed.hpp"

#include "moveParams.h"
#include <cmath>

void Drive :: faceToPoint (
    Point targetPoint,
    optional<QAngularSpeed> vel,
    optional<QAngularAcceleration> accel,
    optional<double> kp,
    optional<QTime> timeout,
    optional<QAngle> end_tolerance 
) {
    // ========= Set Optional to Defaults defined in moveParams.h ========= 
    if (vel == nullopt) vel = MAX_ANG_SPEED;
    if (accel == nullopt) accel = MAX_ANG_ACCEL;
    if (kp == nullopt) kp = KP_ANG;
    if (timeout == nullopt) timeout = TIMEOUT;
    if (end_tolerance == nullopt) end_tolerance = ANG_TOLERANCE;
   
    // ============= Setup Main Loop ============= 
    auto initial_pos = OdomArc::getPos();
    auto initial_angle = initial_pos.theta;
    MotionProfilingAngle mt_profile (initial_pos, targetPoint, *accel, *vel);
    double current_kp = *kp;
    
    auto start = pros::c::millis();
    bool mainLoop = true;
    
    // ============= Main Loop ============= 
    while (mainLoop) {
        // get current conditions
        QTime elapsed = (pros::c::millis() - start) * 1_ms;
        auto current_pos = OdomArc::getPos();

        // ============= Calculate the motion profiling & forward motion vel ============= 
        QAngle angle_delta_current = Math::restrictAngle180(current_pos.theta - initial_angle); 
        QAngle ang_error = (mt_profile.dist(elapsed) - angle_delta_current);
        double turn_motor_vel = ang_error.convert(okapi::radian) * current_kp;

        // ============= Move Robot ============= 
        drive.moveArcade(
            0,
            turn_motor_vel
        );

        // ============= Check if end program ============= 
        if (
            (elapsed >= (mt_profile.get_total_time() + (*timeout))) ||  // timeout
            (abs(ang_error) <= (*end_tolerance))                   // end tolerance
        ) {
            mainLoop = false;
            break;
        }

        // ============= Delay ============= 
        pros::delay(10);
    }

    drive.moveArcade(0,0); // ensure movement stops at end.
}