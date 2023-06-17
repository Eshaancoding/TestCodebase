#ifndef AUTONSELECTOR_H
#define AUTONSELECTOR_H

#include "display/lv_core/lv_obj.h"
#include "display/lvgl.h" // display library  
#include <string>
using namespace std;

namespace AutonSelector {
    static bool isRisky = false;
    static bool isLeft = false;
    static bool shouldTest = false;
    static bool isReady = false;

    void init ();
};

#endif