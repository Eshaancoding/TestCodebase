#ifndef ROUTES_H
#define ROUTES_H

#include "drive.h"
#include "effectors.h"

namespace Routes {
    void test (); // test function
    void left ();   // when robot is on the left side of the goal (long side, can directly do roller)
    void right ();  // when robot is on the right side of the goal (short side, have to move to do roller)
};

#endif