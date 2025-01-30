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
#define WHEEL_DIA 2.9

// too low distance -->  higher wheel dia
// too high distance

namespace OdomArc {
    std::atomic<okapi::QAngle> currentAngle = 0_deg;
    std::atomic<okapi::QLength> xPos = 0_in;
    std::atomic<okapi::QLength> yPos = 0_in;
    std::atomic<bool> calibrating;

    pros::Rotation vert_track_wheel (16);  //16, og 8
    pros::Rotation strafe_track_wheel (8); //8, og 14

    okapi::IMU imu (8, okapi::IMUAxes::z); // imu

    double prevEnc = 0.0;
    double offsetEnc = 0.0;
    double offsetEncBack = 0.0;

    double prevDi = 0.0;
    double prevDib = 0.0;
    double prevAng = 0.0;

    double distanceGet() {
        return -vert_track_wheel.get_position() * ((PI*WHEEL_DIA)/36000); // ticks -> inches
    }

    double distanceb(){
        return strafe_track_wheel.get_position() * ((PI*WHEEL_DIA)/36000);
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

            double ang = angleGet(); // angle of robot in rad
            double Dang = ang - prevAng; // delta angle

            double rFront = Ddi/Dang;
            double rBack = Ddib/Dang;

            // forward
            double xarc_f = rFront*(1-cos(Dang));
            double yarc_f = rFront*(sin(Dang));

            // backward
            double xarc_b = rBack * sin(Dang);
            double yarc_b = rBack * (1 - cos(Dang));

            if (true) { // set true to debug
                Console::printBrain(4, "x: %f y: %f ang: %f",(float)xPos.load().convert(okapi::tile), (float)yPos.load().convert(okapi::tile), ang * 180/PI);
                // Console::printBrain(5, "xarc_f: %f", (float)xarc_f);
                // Console::printBrain(6, "yarc_f: %f", (float)yarc_f);
                // Console::printBrain(7, "di: %f IMU: %f", (float)di, (float)ang);
                // Console::printBrain(8, "Vert Tracking wheel front: %f", (float)vert_track_wheel.get_position());
            }

            // add delta x and delta y from front and back tracking wheel together
            xPos = (xPos.load().convert(okapi::inch) + xarc_f*cos(ang) + yarc_f*(sin(ang))) * 1_in;
            yPos = (yPos.load().convert(okapi::inch) + (-xarc_f*cos(ang)) + yarc_f*cos(ang)) * 1_in;

            /* old code w/o back tracking wheel in case something goes horribly wrong
            xPos = (xPos.load().convert(okapi::inch) + xarc*cos(ang) + yarc*(sin(ang))) * 1_in;
            yPos = (yPos.load().convert(okapi::inch) + (-xarc*cos(ang)) + yarc*cos(ang)) * 1_in;
            */

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