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
#define WHEEL_DIA 2.62

// too low distance -->  higher wheel dia
// too high distance

namespace OdomArc {
    std::atomic<okapi::QAngle> currentAngle = 0_deg;
    std::atomic<okapi::QLength> xPos = 0_in;
    std::atomic<okapi::QLength> yPos = 0_in;
    std::atomic<bool> calibrating;

    pros::Rotation vert_track_wheel (4);
    pros::Rotation strafe_track_wheel (14);

    okapi::IMU imu (16, okapi::IMUAxes::z); // imu

    double prevEnc = 0.0;
    double offsetEnc = 0.0;
    double offsetEncBack = 0.0;

    double prevDi = 0.0;
    double prevDib = 0.0;
    double prevAng = 0.0;

    double distanceGet() {
        return vert_track_wheel.get_position() * ((PI*WHEEL_DIA)/3600); // ticks -> inches
    }

    double distanceb(){
        return strafe_track_wheel.get_position() * ((PI*WHEEL_DIA)/3600);
    }

    double angleGet () { // in angle
        return imu.get() * PI / 180;
    }

    void init (QAngle init_angle) {
        calibrating = true;
        imu.calibrate();
        imu.reset(init_angle.convert(okapi::degree));
        prevDi = 0;
        prevAng = init_angle.convert(okapi::degree); // ehhh not sure
        prevDib = 0;
        calibrating = false;
        offsetEnc = distanceGet();
        offsetEncBack = distanceb();

        pros::delay(1000);

        strafe_track_wheel.reset();
        vert_track_wheel.reset();
        strafe_track_wheel.reset_position();
        vert_track_wheel.reset_position();

        xPos = 0_in;
        yPos = 0_in;
        currentAngle = init_angle;
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

            double ang = angleGet();
            double Dang = ang - prevAng;

            double radius = Ddi/Dang;

            Console::printBrain(4, "y %f", radius*sin(Dang) + (Ddib/Dang)*(1 - cos(Dang)));
            Console::printBrain(5, "x %f", radius*(1-cos(Dang)) - (Ddib/Dang)*(sin(Dang)));
            Console::printBrain(6, "radius: %f", (float)radius);
            Console::printBrain(7, "IMU: %f", (float)ang);
            Console::printBrain(8, "Strafe Tracking wheel front: %f", (float)strafe_track_wheel.get_position());
            Console::printBrain(9, "Vert Tracking wheel front: %f", (float)vert_track_wheel.get_position());

            // end goal: find change in x and change in y (and then do that coord system stuff but uh we worry about that later)
            xPos = (xPos.load().convert(okapi::inch) + radius*(1-cos(Dang)) - (Ddib/Dang)*(sin(Dang))) * 1_in;
            yPos = (yPos.load().convert(okapi::inch) + radius*sin(Dang) + (Ddib/Dang)*(1 - cos(Dang))) * 1_in;
            currentAngle = ang * 1_rad;

            prevDi = di;
            prevAng = ang;
            prevDib = dib;

            //prevEnc = currentEnc; 
            pros::delay(25); 
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
};