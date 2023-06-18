#include "Odom/OdomSim.h"
#include "parameters.h"

OdomSim :: OdomSim () {
    currentAngle = 0_deg;
    xPos = 0_in;
    yPos = 0_in;

    vel = 0_in;
    angleVel = 0_deg;
}

okapi::OdomState OdomSim::getPos () {
    return {xPos, yPos, currentAngle};
};

void OdomSim::setPos (okapi::OdomState state) {
    xPos = state.x;
    yPos = state.y;
    currentAngle = state.theta;
}

void OdomSim::step (double distance, double heading) {
    // change vel
    vel += (distance * ACC);
    if (okapi::abs(vel) > MAX_VEL) vel = MAX_VEL * (vel < 0_in ? -1 : 1);

    // change angle vel
    angleVel += (heading * ACC_ANG);
    if (okapi::abs(angleVel) > MAX_ACC_ANG) angleVel = MAX_ACC_ANG * (vel < 0_in ? -1 : 1);

    // decel 
    if (okapi::abs(vel) > 0_in) vel += -1 * vel * DECEL_CONSTANT;
    if (okapi::abs(angleVel) > 0_deg) angleVel += -1 * angleVel * ANGLE_DECEL_CONSTANT;

    // apply to local coordinates
    xPos += vel * okapi::cos(currentAngle);
    yPos += vel * okapi::sin(currentAngle);
    currentAngle += angleVel;
}