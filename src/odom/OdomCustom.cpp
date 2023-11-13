#include "odom/OdomCustom.h"
#include "Odom/OdomOkapi.h"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"
#include "parameters.h"
#include "OdomOkapi.h"
#include "Console.h"

#define PI 3.14159265
#define WHEEL_DIA 2.763715082

namespace OdomCustom {
    std::atomic<okapi::QAngle> currentAngle = 0_deg;
    std::atomic<okapi::QLength> xPos = 0_in;
    std::atomic<okapi::QLength> yPos = 0_in;

    okapi::IMU imu (13, okapi::IMUAxes::z);
    okapi::RotationSensor enc (16);
    double prevAng = 0.0;
    double prevEnc = 0.0;

    void MainLoop () {
        enc.reset();
        imu.calibrate();
        pros::delay(2000);
        double offsetEnc = enc.get();
        double offsetIMU = imu.get() * PI/180;
    
        while (true) {
            // get change in encoder
            double currentEnc = (enc.get() - offsetEnc)/360;            
            double diff = currentEnc - prevEnc;
            diff *= PI * WHEEL_DIA; // convert to inches


            // get change in angle
            double currentAng = ((imu.get() * PI / 180) - offsetIMU);
            double changeAng = (currentAng - prevAng);
            xPos = (xPos.load().convert(okapi::inch) + diff * sin(currentAng)) * 1_in;
            yPos = (yPos.load().convert(okapi::inch) + diff * cos(currentAng)) * 1_in;

            // set previous values
            prevEnc = currentEnc; 
            prevAng = currentAng;
            pros::delay(50);
        }
        

        // while (true) {
        //     // get change in encoder
        //     double currentEnc = (enc.get() - offsetEnc)/360;            
        //     double diff = currentEnc - prevEnc;
        //     diff *= PI * WHEEL_DIA; // convert to inches

        //     // get change in angle
        //     double currentAng = ((imu.get() * PI / 180) - offsetIMU);
        //     double diffAng = currentAng - prevAng;            
            
        //     // MAKE SURE IT IS IN RADIANS :D

        //     // calculate radius
        //     double radius = diff / diffAng;            

        //     // find delta x and y
        //     double deltaXPos = diffAng == 0 ? 0 : (2 * pow(sin(diffAng/2), 2) * radius);
        //     double deltaYPos = diffAng == 0 ? diff : (2 * sin(diffAng/2) * cos(diffAng/2) * radius);


        //     // do relative to absolute coordinate
        //     // could be reverse counterclockwise to clockwise
        //     // xPos = ((deltaXPos - xPos.load().convert(okapi::inch)) * cos(diffAng) +  (deltaYPos - yPos.load().convert(okapi::inch)) * sin(diffAng)) * 1_in;
        //     // yPos = (-(deltaXPos - xPos.load().convert(okapi::inch)) * sin(diffAng) + (deltaYPos - yPos.load().convert(okapi::inch)) * cos(diffAng)) * 1_in;
        //     yPos = (yPos.load().convert(okapi::inch) + deltaYPos * cos(currentAng)) * 1_in;
        //     xPos = (xPos.load().convert(okapi::inch) + deltaXPos * sin(currentAng)) * 1_in;

        //     // debug
        //     Console::printBrain(0, diffAng, "theta delta: ");
        //     Console::printBrain(1, deltaXPos, "x delta: ");
        //     Console::printBrain(2, deltaYPos, "y delta: ");
            Console::printBrain(3, xPos.load().convert(okapi::inch), "x: ");
            Console::printBrain(4, yPos.load().convert(okapi::inch), "y: ");
        //     Console::printBrain(5, currentEnc, "current enc: ");
        //     Console::printBrain(6, currentAng, "current ang: ");

        //     // set previous values
        //     prevEnc = currentEnc; 
        //     prevAng = currentAng;
        //     pros::delay(50);
        // }
    }

    // right = clockwise = +

    // get position
    okapi::OdomState getPos () {
        return {xPos.load(), yPos.load(), currentAngle.load()};
    }

    // set position
    void setPos (okapi::OdomState state) {
        xPos = state.x;
        yPos = state.y;
        currentAngle = state.theta;
    }
};