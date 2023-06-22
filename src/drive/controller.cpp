#include "controller.h"
#include "Console.h"

namespace Control {
    pros::Controller controller (pros::E_CONTROLLER_MASTER);
 
    double getAnalog (controller_analog_e_t channel) {
        return controller.get_analog(channel)/127.0;
    }

    bool getButtonPressed (pros::controller_digital_e_t button) {
        return controller.get_digital(button);
    }

    bool getDebouncePressed (pros::controller_digital_e_t button) {
        return controller.get_digital_new_press(button); 
    }

    template <typename... Arg>
    void printController (int line, std::string str, Arg ...param) {
        controller.print(line, 0, str, param...);
    }
}