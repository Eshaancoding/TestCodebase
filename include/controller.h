#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "main.h"
#include "okapi/impl/device/controllerUtil.hpp"
#include <string>
using namespace okapi;
using namespace pros;

// literally just a overhead wrapper with get debounce.
// idk why I created my own class for this its what it is tho :/
// defined in drive/controller.cpp

namespace Control { 
    static pros::Controller controller (pros::E_CONTROLLER_MASTER);
    double getAnalog (controller_analog_e_t channel);  // returns -1 to 1
    bool getButtonPressed (pros::controller_digital_e_t button);
    bool getDebouncePressed (pros::controller_digital_e_t button);

    template <typename... Arg>
    void printController (uint8_t line, std::string str, Arg ...param) {
        controller.print(line, 0, str.c_str(), param...);
    }
};   

#endif