#include "odom/OdomOkapi.h"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/api/odometry/odomState.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"
#include "parameters.h"
#include "Math.h"
#include "Console.h"

#define WHEEL_DIM       3.152_in  // Diameter of robot wheel
#define WHEEL_TRACK     13.895_in  // Distance from center of the bottom left wheel to the center of the bottom right wheel

// Remember, if you are changing the configuation a little bit, then make sure you change the rest of the functions like getting right encoder count

// iterations per revolution; 60/48 because there's a gear ratio :)
const double itpr = okapi::imev5BlueTPR * 60.0 / 48.0 ;

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
            okapi::ChassisScales({WHEEL_DIM, WHEEL_TRACK}, itpr)
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

double OdomOkapi::getLeftRevs  () {
    Console::printBrain(6, "leftt0: %.3f left1: %.3f", leftMotorGroup.getEncoder(0)->get(), leftMotorGroup.getEncoder(1)->get());
    return (leftMotorGroup.getEncoder(0)->get() + leftMotorGroup.getEncoder(1)->get()) / (2 * itpr);
}

double OdomOkapi::getRightRevs  () {
    Console::printBrain(5, "right0: %.3f right1: %.3f", rightMotorGroup.getEncoder(0)->get(), rightMotorGroup.getEncoder(1)->get());

    return (rightMotorGroup.getEncoder(0)->get() + rightMotorGroup.getEncoder(1)->get()) / (2 * itpr);
}

double OdomOkapi::getMiddleRevs () {
    return 0; // for this configuration we don't have middle encoder
}