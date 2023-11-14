#ifndef ODOMCUSTOM_H
#define ODOMCUSTOM_H

#include "main.h"
#include "Math.h"
#include "parameters.h"
#include <iostream>
using namespace std;

namespace OdomCustom {
    void init ();
    void MainLoop ();

    okapi::OdomState getPos();
    void setPos (okapi::OdomState state);

    double getRevs  ();
};


#endif 