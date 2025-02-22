#include "controller.h"
#include "drive.h"
#include "Odom/Math.h"
#include "motionProfilingAngle.h"
#include "odom/OdomArc.h"
#include "okapi/api/odometry/odomState.hpp"
#include "okapi/api/units/QAngle.hpp"
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
    MotionProfilingAngle mt_profile (
        initial_pos, 
        targetPoint, 
        *accel, 
        *vel
    );
    double current_kp = *kp;
    
    bool mainLoop = true;
    
    QAngle min_ang_err = 0_deg;
    QAngle max_ang_err = 0_deg;
    bool stbool = true;
    
    // Testing
    // QTime tTest = 0.0_s;
    // while (tTest <= 2.0_s) {
    //     printf("* Vel: %f *\n", mt_profile.vel(tTest).convert(dps));
    //     mt_profile.target_point(tTest);
    //     tTest += 0.1_s; 
    //     pros::delay(200);
    // }
    
    // ============= Main Loop ============= 
    auto start = pros::c::millis();
    while (mainLoop) {
        // get current conditions
        QTime elapsed = (pros::c::millis() - start) * 1_ms;
        auto current_pos = OdomArc::getPos();

        // ============= Calculate the motion profiling & forward motion vel ============= 
        Point t_point = mt_profile.target_point(elapsed);
        QAngle ang_error = Math::anglePoint(current_pos, t_point);
        double turn_motor_vel = ang_error.convert(okapi::degree) * current_kp + KI_ANG;

        if (ang_error < min_ang_err || stbool) min_ang_err = ang_error;
        if (ang_error > max_ang_err || stbool) max_ang_err = ang_error;
        stbool = false;

        // ============= Debug ============= 
        if (true) {
            auto t1 = (current_pos.theta - initial_pos.theta).abs();
            auto t2 = Math::anglePoint(initial_pos, t_point);
            printf("* Motion Profile Vel: %f *\n", mt_profile.vel(elapsed).convert(dps) * M_PI / 180);
            printf("* Target Ang: %f *\n", t2.convert(radian));
            printf("* Current Ang: %f *\n", t1.convert(radian));
            // printf("* Turn motor vel: %f *\n", turn_motor_vel / 600);
            printf("********************\n");
        }

        // ============= Move Robot ============= 
        drive.moveArcade(
            0,
            (turn_motor_vel / 600)
        );

        // ============= Check if end program ============= 
        if (
            (elapsed >= (mt_profile.get_total_time() + (*timeout))) ||  // timeout
            (abs(Math::anglePoint(current_pos, targetPoint)) <= (*end_tolerance))                   // end tolerance
        ) {
            mainLoop = false;
            break;
        }

        // ============= Delay ============= 
        pros::delay(10);
    }

    if (true) {
        Control::printController(0, "%.3f to %.3f", min_ang_err.convert(degree), max_ang_err.convert(degree));
    }

    drive.moveArcade(0,0); // ensure movement stops at end.
}