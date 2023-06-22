#include "parameters.h"
#include "Odom/OdomParamHelper.h"
#include "Controller.h"
#include "okapi/api/util/mathUtil.hpp"
#include "drive.h"
#include "Console.h"
#include "pros/misc.h"

/**
 * @brief run the mathematics to get wheel diameter dimensions and track dimensions
 * wheel dia math: 
 *    total inches = num rot * pi * wheel diameter (circumference = pi * diameter)
 *    24_in = num_rot * pi * diameter (moving 1_tile = 24 inches of movement)
 *    diameter = 24_in / (num_rot * pi) 
 *        final equation; num_rot comes from the odometery: number of rotation/revolutions from encoder wheel

 * tracking wheel dia
 *     Two equations: arc length = radius * theta (circle basics, theta must be in radians)
 *                    arc length = num rot * wheel dia * pi (again, circumference with num rot)
 *     Set them equal to each other:
 *                    radius * theta = num rot * wheel dia * pi 
 *                    radius * 2 * pi = num rot * wheel dia * pi (theta = 2pi since we are doing 360 deg rotation)
                      radius * 2 = num rot * wheel dia (cancel out pi)
                      radius = (num rot * wheel dia) / 2

    Note we could use wheel dia from the previous calculations
    In terms of the num rot, we are just going to average from the left and right side of the encoders
 */

void OdomParamHelper :: run () {
    Control::printController(0, "Move robot 1 tile forward/backward (A to done)");

    int lineNum = -1;

    // get wheel dia
    double forwardWheelDia;
    while (true) {
        double analogLeftY = Control::getAnalog(E_CONTROLLER_ANALOG_RIGHT_Y);
        
        drive.moveArcade(analogLeftY, 0);

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_A)) {
            double left = std::abs(odometery.getLeftRevs());            
            double right = std::abs(odometery.getRightRevs());

            Console::printBrain(++lineNum, "Left %.3f Right %.3f", left, right);

            double numRot = (left + right) / 2;
            forwardWheelDia = 24.0 / (numRot * pi);
            Console::printBrain(++lineNum, "Wheel Dia: %.3f", forwardWheelDia);

            break;
        }

        pros::delay(10);
    }

    // get wheel dia for mid tracking wheel
    double midWheelDia;
    if (MID_TRACKING_WHEEL_BOTTOM != ' ' && MID_TRACKING_WHEEL_TOP != ' ') {
        Control::printController(0, "Move robot 1 tile to the left/right (A to done)");
        // we have valid mid tracking wheel lol
        while (true) {
            if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_A)) {
                double numRot = std::abs(odometery.getMiddleRevs());
                midWheelDia = 24.0 / (numRot * pi);
                Console::printBrain(++lineNum, "Mid Wheel Dia: %.3f", midWheelDia);
                break;
            }

            pros::delay(10);
        }
    }

    // get tracking dimensions
    Control::printController(0, "Move robot 360 deg (A to done)");
    while (true) {
        double analogLeftY = Control::getAnalog(E_CONTROLLER_ANALOG_RIGHT_Y);
        
        drive.moveArcade(0, analogLeftY);

        if (Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_A)) {
            double left = std::abs(odometery.getLeftRevs());            
            double right = std::abs(odometery.getRightRevs());
            double numRot = (left + right) / 2;

            double radius = (numRot * forwardWheelDia) / 2;
            Console::printBrain(++lineNum, "Forward Radius: %.3f", radius);

            if (MID_TRACKING_WHEEL_BOTTOM != ' ' && MID_TRACKING_WHEEL_TOP) {
                numRot = std::abs(odometery.getRightRevs());
                radius = (numRot * midWheelDia) / 2;
                Console::printBrain(++lineNum, "Backward Radius: %.3f", radius);
            }
            break;
        }

        pros::delay(10);
    }

    Control::printController(0, "Done!");
};