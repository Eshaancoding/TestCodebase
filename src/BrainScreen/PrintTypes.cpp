#include "BrainScreen/Console.h"
#include <string>

void Console::printBrain(int lineNum, OdomState state, string label) {
    label += (label.size() > 0 ? ": " : "");

    printBrain(lineNum, "%sx: %.3fin y: %.3fin theta: %.3fdeg", label.c_str(), 
        state.x.convert(okapi::inch), 
        state.y.convert(okapi::inch), 
        state.theta.convert(okapi::degree)
    );
}

void Console::printBrain(int lineNum, QAngle ang, string label) {
    label += (label.size() > 0 ? ": " : "");

    printBrain(lineNum, "%s%.3fdeg", label.c_str(), ang.convert(okapi::degree));
}

void Console::printBrain(int lineNum, QLength length, string label) {
    label += (label.size() > 0 ? ": " : "");

    printBrain(lineNum, "%s%.3fin", label.c_str(), length.convert(okapi::inch));
}

void Console::printBrain(int lineNum, Point p, string label) {
    label += (label.size() > 0 ? ": " : "");

    printBrain(lineNum, "%sx: %.3fin y: %.3fin", label.c_str(), p.x.convert(okapi::inch), p.y.convert(okapi::inch));
}

void Console::printBrain(int lineNum, double n, string label) {
    label += (label.size() > 0 ? ": " : "");

    printBrain(lineNum, "%s%.3f", label.c_str(), n);
}
