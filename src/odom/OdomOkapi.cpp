#include "OdomOkapi.h"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/api/odometry/odomState.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"
#include "parameters.h"
#include "OdomMath.h"

OdomOkapi :: OdomOkapi () {
    auto builder = okapi::ChassisControllerBuilder();
    builder
        .withMotors(
            leftMotorGroup,
            rightMotorGroup
        );
        
    // check if mid tracking wheels is valid
    if (MID_TRACKING_WHEEL_BOTTOM != ' ' && MID_TRACKING_WHEEL_TOP != ' ') {
        builder.withDimensions(
            okapi::AbstractMotor::gearset::green,
            okapi::ChassisScales({WHEEL_DIM, WHEEL_TRACK, TRACKING_WHEEL_BACK, WHEEL_DIM}, okapi::imev5GreenTPR)
        );

        builder.withSensors(
            okapi::ADIEncoder(
                LEFT_TRACKING_WHEEL_TOP,
                LEFT_TRACKING_WHEEL_BOTTOM
            ),

            okapi::ADIEncoder(
                RIGHT_TRACKING_WHEEL_TOP,
                RIGHT_TRACKING_WHEEL_BOTTOM
            ),

            okapi::ADIEncoder(
                MID_TRACKING_WHEEL_TOP,
                MID_TRACKING_WHEEL_BOTTOM
            )
        );
    }
    else {
        builder.withDimensions(
            okapi::AbstractMotor::gearset::green, 
            okapi::ChassisScales({WHEEL_DIM, WHEEL_TRACK}, okapi::imev5GreenTPR)
        );
        builder.withSensors(
            okapi::ADIEncoder(
                LEFT_TRACKING_WHEEL_TOP,
                LEFT_TRACKING_WHEEL_BOTTOM
            ),

            okapi::ADIEncoder(
                RIGHT_TRACKING_WHEEL_TOP,
                RIGHT_TRACKING_WHEEL_BOTTOM
            ) 
        );
        
    }

    chassis = builder.buildOdometry();
}

okapi::OdomState OdomOkapi::getPos () {
    auto state = chassis->getState();
    return {
        state.x,
        state.y,
        Math::restrictAngle180(state.theta) 
    };
}

void OdomOkapi::setPos (okapi::OdomState state) {
    chassis->setState(state);
}