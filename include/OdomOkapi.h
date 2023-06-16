#ifndef ODOM_H
#define ODOM_H

#include "main.h"
#include <memory>

class OdomOkapi {
private:
    std::shared_ptr<okapi::OdomChassisController> chassis;
public: 
    OdomOkapi ();

    okapi::OdomState getPos ();

    void setPos (okapi::OdomState state);
};

#endif