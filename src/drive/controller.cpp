#include "controller.h"
#include "Console.h"

namespace Control {
 
    double getAnalog (controller_analog_e_t channel) {
        return controller.get_analog(channel)/127.0;
    }

    bool getButtonPressed (pros::controller_digital_e_t button) {
        return controller.get_digital(button);
    }

    bool getDebouncePressed (pros::controller_digital_e_t button) {
        return controller.get_digital_new_press(button); 
    }

    
}