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
    okapi::RotationSensor enc (16);
    double prevEnc = 0.0;
    int index = 0;

    void MainLoop () {
        enc.reset();
        pros::delay(2000);
        double offsetEnc = enc.get();

        while (true) {
            double currentEnc = (enc.get() - offsetEnc)/360;            
            double diff = currentEnc - prevEnc;

            Console::printBrain(0, currentEnc, "Curr: ");
            Console::printBrain(1, prevEnc, "Prev: ");
            Console::printBrain(2, diff, "Diff: ");
            Console::printBrain(3, xPos, "Inches: ");

            // this is... kinda temporary
            xPos = xPos.load() + ((diff * PI * WHEEL_DIA) * 1_in);

            prevEnc = currentEnc; 
            pros::delay(50);

            index += 1;
        }
    }

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