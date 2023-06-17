#ifndef BRAINSCREEN_H
#define BRAINSCREEN_H

#include "display/lvgl.h" // display library  
#include "main.h"
#include <vector>
#include <string>
using namespace std;

namespace AutonSelector {
    static bool isRisky = false;
    static bool isLeft = false;
    static bool shouldTest = true;
    static bool isReady = true;

    void init ();
    
};



#endif