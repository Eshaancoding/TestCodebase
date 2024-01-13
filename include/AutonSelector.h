#ifndef BRAINSCREEN_H
#define BRAINSCREEN_H

#include "display/lvgl.h" // display library  
#include "main.h"
#include <vector>
#include <string>
using namespace std;

namespace AutonSelector {
    enum SideState {ELIM=0, QUAL=1};
    enum RiskyState {OFFENSIVE=0, DEFENSIVE=1};
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