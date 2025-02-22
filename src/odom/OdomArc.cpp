#include "odom/OdomCustom.h"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"
#include "parameters.h"
#include <cmath>
#include "Console.h"
#include "pros/rotation.hpp"

#define PI 3.14159265
#define WHEEL_DIA_VERT 2.0
#define WHEEL_DIA_STRAFE 2.9

// too low distance -->  higher wheel dia
// too high distance

namespace OdomArc {
    std::atomic<okapi::QAngle> currentAngle = 0_deg;
    std::atomic<okapi::QLength> xPos = 0_in;
    std::atomic<okapi::QLength> yPos = 0_in;
    std::atomic<okapi::QLength> distTravelled = 0_ft; 
    std::atomic<bool> calibrating;

    pros::Rotation vert_track_wheel (13);  // vert 13
    pros::Rotation strafe_track_wheel (14); // strafe 

    okapi::IMU imu (7, okapi::IMUAxes::z); // imu


    double prevDi = 0.0;
    double prevDib = 0.0;
    double prevAng = 0.0;

    double distanceGet() {
        return vert_track_wheel.get_position() * ((PI*WHEEL_DIA_VERT)/36000);  // ticks --> inches
    }

    double distanceb(){
        // tune it such that positive values from the backward wheel means robot is going into the -x axis
        return strafe_track_wheel.get_position() * ((PI*WHEEL_DIA_STRAFE)/36000); // ticks --> inches
    }

    double angleGet () { // in angle
        return imu.get() * PI / 180;
    }

    void init (QAngle init_angle) {
        calibrating = true;
        imu.calibrate();
        imu.reset(init_angle.convert(okapi::degree));
        prevDi = 0;
        prevAng = init_angle.convert(okapi::radian); // ehhh not sure
        prevDib = 0;
        calibrating = false;

        pros::delay(1000);

        strafe_track_wheel.reset();
        vert_track_wheel.reset();
        strafe_track_wheel.reset_position();
        vert_track_wheel.reset_position();

        xPos = 0_in;
        yPos = 0_in;
        currentAngle = init_angle;

        distTravelled = 0_ft;
    }

    /*
    forward: positive y
    backward: negative y 
    +90 deg: clockwise 
    -90 deg: counterclockwise
    right: positive x
    left: negative x
    take into account the 180 thing, angle goes from -180 to 180
    */

    void MainLoop () {
        while (true) {

            // get change in encoder
            double di = distanceGet(); // arc length
            double Ddi = di - prevDi;

            double dib = distanceb(); // arc length back
            double Ddib = dib - prevDib;

            double ang = angleGet(); // angle of robot in rad
            double Dang = ang - prevAng + 1e-10; // delta angle

            double rFront = Ddi/Dang;
            double rBack = Ddib/Dang;

            // forward
            double xarc_f = rFront * (1 - cos(Dang));
            double yarc_f = rFront * sin(Dang);

            // backward
            double xarc_b = rBack * (1 - cos(Dang));
            double yarc_b = rBack * sin(Dang);

            if (false) { // set true to debug
                Console::printBrain(4, "x: %f y: %f ang: %f",(float)xPos.load().convert(okapi::tile), (float)yPos.load().convert(okapi::tile), ang * 180/PI);
                Console::printBrain(5, "Vert Tracking wheel front: %f", (float)vert_track_wheel.get_position());
                Console::printBrain(6, "Vert Tracking wheel back: %f", (float)strafe_track_wheel.get_position());
                Console::printBrain(7, "Total Distance: %f ft | %f tile", (float)distTravelled.load().convert(foot), (float)distTravelled.load().convert(tile));
                Console::printBrain(8, "Dangle: %f", Dang);
            }

            double f_xd =  xarc_f * cos(ang)          + yarc_f * sin(ang);  // x delta from forward tracking wheel
            double f_yd = -xarc_f * cos(ang)          + yarc_f * cos(ang); // y delta from forward tracking wheel
            double b_xd =  xarc_b * cos(ang - (PI/2)) + yarc_b * sin(ang - (PI/2));  // x delta from backward tracking wheel (note that positive values from backward sensor --> robot going in positive x-axis)
            double b_yd = -xarc_b * cos(ang - (PI/2)) + yarc_b * cos(ang - (PI/2));  // y delta from backward tracking wheel (note that positive values from backward sensor --> robot going in positive x-axis)

            xPos = (xPos.load().convert(okapi::inch) + f_xd + b_xd) * 1_in;
            yPos = (yPos.load().convert(okapi::inch) + f_yd + b_yd) * 1_in;

            // calculate delta distance travelled 
            QLength delta_d = sqrt(pow(f_xd + b_xd, 2) + pow(f_yd + b_yd, 2)) * 1_in;
            distTravelled = distTravelled.load() + delta_d;

            // update internal variables
            currentAngle = ang * 1_rad;
            prevDi = di;
            prevAng = ang;
            prevDib = dib;

            pros::delay(10); 
        }
    }

    // get position-
    okapi::OdomState getPos () {
        return {xPos.load(), yPos.load(), currentAngle.load()};
    }

    // set position
    void setPos (std::optional<okapi::QLength> x, std::optional<okapi::QLength> y, std::optional<okapi::QAngle> angle) {
        if (x) xPos = *x;
        if (y) yPos = *y;
        if (angle) {
            currentAngle = *angle;
            imu.reset((*angle).convert(okapi::degree));
        }
    }

    // calibrating
    bool isCalibrating () {
        return calibrating.load();
    }

    void resetDistTravelled () {
        distTravelled = 0_ft; // atomic set
    }

    QLength getDistTravelled () {
        return distTravelled.load();
    }
};