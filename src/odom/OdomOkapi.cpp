#include "odom/OdomOkapi.h"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/api/odometry/odomState.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"
#include "parameters.h"
#include "Math.h"

OdomOkapi :: OdomOkapi () {

    chassis = okapi::ChassisControllerBuilder()
        .withMotors(
            leftMotorGroup,
            rightMotorGroup
        )
        .withDimensions(
            AbstractMotor::GearsetRatioPair(
                okapi::AbstractMotor::gearset::blue, 1
            ),
            okapi::ChassisScales({WHEEL_DIM, WHEEL_TRACK}, okapi::imev5BlueTPR*60.0/48.0)
        )
        .withOdometry()
        .buildOdometry();
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