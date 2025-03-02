#include "odom/Math.h"
#include "okapi/api/units/QAcceleration.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include <cmath>
#include <sys/_intsup.h>
#include "Console.h"
#include "okapi/api/units/QSpeed.hpp"
#include "okapi/api/units/QTime.hpp"
#include "pros/rotation.hpp"
#include "pros/rtos.hpp"

#define PI 3.14159265
#define WHEEL_DIA_VERT 2.0
#define WHEEL_DIA_STRAFE 2.0

// too low distance -->  higher wheel dia
// too high distance

namespace OdomArc {
    std::atomic<okapi::QAngle> currentAngle = 0_deg;
    std::atomic<okapi::QLength> xPos = 0_in;
    std::atomic<okapi::QLength> yPos = 0_in;
    std::atomic<okapi::QLength> distTravelled = 0_ft; 
    std::atomic<okapi::QSpeed> current_speed = 0_fps;  // in feet per sec
    std::atomic<bool> calibrating;

    pros::Rotation vert_track_wheel (13);  // vert 13
    pros::Rotation strafe_track_wheel (20); // strafe 

    okapi::IMU imu (6, okapi::IMUAxes::z); // imu


    QLength prevDi = 0.0_in;
    QLength prevDib = 0.0_in;
    QAngle prevAng = 0.0_rad;
    QTime prevTime = 0_s;

    QLength distanceGet() {
        return vert_track_wheel.get_position() * ((PI*WHEEL_DIA_VERT)/36000) * 1_in;  // ticks --> inches
    }

    QLength distanceb() {
        // tune it such that positive values from the backward wheel means robot is going into the -x axis
        return strafe_track_wheel.get_position() * ((PI*WHEEL_DIA_STRAFE)/36000) * 1_in; // ticks --> inches
    }

    QAngle angleGet () { // in angle
        return imu.get() * PI / 180 * 1_rad;
    }

    void init (QAngle init_angle) {
        calibrating = true;
        imu.calibrate();
        imu.reset(init_angle.convert(okapi::degree));
        prevDi = 0_in;
        prevAng = init_angle; // ehhh not sure
        prevDib = 0_in;
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
        prevTime = pros::millis() * 1_ms;
        auto prevDistTravelled = 0_in;
        unsigned int i = 0;
        while (true) {
            pros::delay(10); 

            // get change in encoder
            QLength di = distanceGet(); // arc length
            QLength Ddi = di - prevDi;

            QLength dib = distanceb(); // arc length back
            QLength Ddib = dib - prevDib;

            QAngle ang = angleGet(); // angle of robot in rad
            double Dang = Math::restrictAngle180(ang - prevAng).convert(radian); // delta angle

            QLength rFront = Dang == 0 ? 0_in : Ddi/Dang;
            QLength rBack  = Dang == 0 ? 0_in : Ddib/Dang;

            // forward
            QLength xarc_f = Dang == 0 ? 0_in : rFront * (1 - cos(Dang));
            QLength yarc_f = Dang == 0 ? Ddi  : rFront * sin(Dang);

            // backward
            QLength xarc_b = Dang == 0 ? 0_in : rBack * (1 - cos(Dang));
            QLength yarc_b = Dang == 0 ? Ddib : rBack * sin(Dang);

            if (true) { // set true to debug
                Console::printBrain(4, "x: %f y: %f ang: %f",(float)xPos.load().convert(okapi::inch), (float)yPos.load().convert(okapi::inch), ang * 180/PI);
                Console::printBrain(5, "Vert Tracking wheel front: %f", (float)vert_track_wheel.get_position());
                Console::printBrain(6, "Vert Tracking wheel back: %f", (float)strafe_track_wheel.get_position());
                Console::printBrain(7, "Total Distance: %f ft | %f tile", (float)distTravelled.load().convert(foot), (float)distTravelled.load().convert(tile));
                Console::printBrain(8, "Dangle: %f", Dang);
            }

            QLength f_xd =  xarc_f * cos(ang)          + yarc_f * sin(ang);  // x delta from forward tracking wheel
            QLength f_yd = -xarc_f * cos(ang)          + yarc_f * cos(ang); // y delta from forward tracking wheel
            QLength b_xd =  xarc_b * cos(ang - (PI/2)*1_rad) + yarc_b * sin(ang - (PI/2)*1_rad);  // x delta from backward tracking wheel (note that positive values from backward sensor --> robot going in positive x-axis)
            QLength b_yd = -xarc_b * cos(ang - (PI/2)*1_rad) + yarc_b * cos(ang - (PI/2)*1_rad);  // y delta from backward tracking wheel (note that positive values from backward sensor --> robot going in positive x-axis)

            xPos = (xPos.load() + f_xd + b_xd);
            yPos = (yPos.load() + f_yd + b_yd);

            // calculate delta distance travelled 
            QLength delta_d = sqrt(pow((f_xd + b_xd).convert(inch), 2) + pow((f_yd + b_yd).convert(inch), 2)) * 1_in;
            distTravelled = distTravelled.load() + delta_d;
            
            // get speed
            if (i % 5 == 0) {
                auto currentTime = pros::millis() * 1_ms;
                auto c = distTravelled.load();
                current_speed = (c - prevDistTravelled) / (currentTime - prevTime);
                prevTime = currentTime;
                prevDistTravelled = c;
            }

            // update internal variables
            currentAngle = ang;
            prevDi = di;
            prevAng = ang;
            prevDib = dib;

            i += 1;
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

    QSpeed getCurrentSpeed () {
        return current_speed.load();
    }
};