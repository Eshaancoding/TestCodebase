#ifndef BRAINSCREEN_H
#define BRAINSCREEN_H

#include "display/lvgl.h" // display library  
#include "main.h"
#include <vector>
#include <string>
using namespace std;

namespace AutonSelector {
    enum ElimQualState {ELIM=0, QUAL=1};
    enum OffDefState {OFFENSIVE=0, DEFENSIVE=1};
    enum Status {NOTREADY, SKILL, ROUTE};

    struct State {
        ElimQualState elimQualState;
        OffDefState offDefState;
        Status status;
    };

    State getState ();
    void init ();
};

#endif