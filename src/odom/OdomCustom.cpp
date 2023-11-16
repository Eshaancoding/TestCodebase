#include "odom/OdomCustom.h"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"
#include "parameters.h"
#include "Console.h"

#define PI 3.14159265
#define WHEEL_DIA 2.763715082

namespace OdomCustom {
    std::atomic<okapi::QAngle> currentAngle = 0_deg;
    std::atomic<okapi::QLength> xPos = 0_in;
    std::atomic<okapi::QLength> yPos = 0_in;
    std::atomic<bool> calibrating;

    okapi::IMU imu (13, okapi::IMUAxes::z);
    okapi::RotationSensor enc (16);
    double prevEnc = 0.0;
    double offsetEnc = 0.0;

    void init (QAngle init_angle) {
        calibrating = true;
        enc.reset();
        imu.calibrate();
        imu.reset(0);
        calibrating = false;
        offsetEnc = enc.get();
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
            double currentEnc = (enc.get() - offsetEnc)/360;            
            double diff = currentEnc - prevEnc;
            diff *= PI * WHEEL_DIA; // convert to inches

            // get change in angle
            double currentAng = (imu.get() * PI / 180);
            xPos = (xPos.load().convert(okapi::inch) + diff * sin(currentAng)) * 1_in;
            yPos = (yPos.load().convert(okapi::inch) + diff * cos(currentAng)) * 1_in;
            currentAngle = currentAng * okapi::radian;

            // set previous values
            prevEnc = currentEnc; 
            pros::delay(25); // test this shit
        }
    }

    // get position
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