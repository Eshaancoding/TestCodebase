#ifndef BRAINSCREEN_H
#define BRAINSCREEN_H

#include "display/lvgl.h" // display library  
#include "main.h"
#include <vector>
#include <string>
using namespace std;

namespace AutonSelector {
    enum SideState {LEFT, RIGHT};
    enum RiskyState {RISKY, NONRISKY};
    enum Status {NOTREADY, TEST, ROUTE};

    struct State {
        SideState side;
        RiskyState risky;
        Status status;
    };

    State getState ();
    void init ();
};



#endif