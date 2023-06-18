#include "odom/OdomCustom.h"
#include "Odom/OdomOkapi.h"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"
#include "parameters.h"

void OdomCustom::MainLoop () {
    // get sensor values and diff
    double le = leftEncoder->get();
    double re = rightEncoder->get();

    // convert sensor values to inches
    double leftDeltaLength = (le - previousLeftEncoder)/360.0 * WHEEL_DIM.convert(okapi::inch) * pi;
    double rightDeltaLength = (re - previousRightEncoder)/360.0 * WHEEL_DIM.convert(okapi::inch) * pi;

    // delta theta
    QAngle deltaTheta = (leftDeltaLength - rightDeltaLength) / (WHEEL_TRACK.convert(okapi::inch)) * okapi::radian;
    
    // mid delta
    double midDeltaLength = 0;
    if (middleEncoder != nullptr) {
        double me = middleEncoder->get();
        midDeltaLength = (me - previousMidEncoder)/360.0 * WHEEL_DIM.convert(okapi::inch) * pi;
        previousMidEncoder = me;

        midDeltaLength -= (deltaTheta.convert(okapi::radian) * TRACKING_WHEEL_BACK.convert(okapi::inch)); // correct for angle change
    }

    // apply xpos & ypos
    double forwardAvg = (leftDeltaLength + rightDeltaLength) / 2;
    xPos += ((forwardAvg * okapi::cos(currentAngle)) - (midDeltaLength * okapi::sin(currentAngle))) * okapi::inch;
    yPos += ((forwardAvg * okapi::sin(currentAngle)) + (midDeltaLength * okapi::cos(currentAngle))) * okapi::inch;

    // apply delta
    currentAngle += deltaTheta;
    currentAngle = OdomMath::constrainAngle180(currentAngle);

    // set previous encoder value
    previousLeftEncoder = le;
    previousRightEncoder = re;
}

OdomCustom::OdomCustom () {
    xPos = 0_in;
    yPos = 0_in; 
    currentAngle = 0_deg;

    leftEncoder = new okapi::ADIEncoder({LEFT_TRACKING_WHEEL_TOP, LEFT_TRACKING_WHEEL_BOTTOM});
    rightEncoder = new okapi::ADIEncoder({RIGHT_TRACKING_WHEEL_TOP, RIGHT_TRACKING_WHEEL_BOTTOM});

    if (MID_TRACKING_WHEEL_BOTTOM != ' ' && MID_TRACKING_WHEEL_TOP != ' ') {
        middleEncoder = new okapi::ADIEncoder({MID_TRACKING_WHEEL_TOP, MID_TRACKING_WHEEL_BOTTOM});
    }
}

okapi::OdomState OdomCustom::getPos() { 
    return {xPos, yPos, currentAngle};
}

void OdomCustom::setPos(okapi::OdomState state) {
    xPos = state.x;
    yPos = state.y;
    currentAngle = OdomMath::constrainAngle180(state.theta);

    leftEncoder->reset();
    rightEncoder->reset();
    previousLeftEncoder = 0;
    previousRightEncoder = 0;

    if (middleEncoder != nullptr) {
        middleEncoder->reset();
        previousMidEncoder = 0;
    }
}