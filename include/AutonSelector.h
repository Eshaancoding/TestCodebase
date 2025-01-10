#ifndef BRAINSCREEN_H
#define BRAINSCREEN_H

#include "display/lvgl.h" // display library  
#include "main.h"
#include <vector>
#include <string>
using namespace std;

namespace AutonSelector {
    enum ElimQualState {ELIM=0, QUAL=1}; // middle button
    enum OffDefState {BLUE=0, RED=1}; // top buttons
    enum Status {NOTREADY, SKILL, ROUTE}; // bottom button; is skills
    

    struct State {
        ElimQualState elimQualState;
        OffDefState offDefState;
        Status status;
    };

    State getState ();
    void init ();
};

#endif