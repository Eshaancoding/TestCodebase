#include "BrainScreen/Console.h"
#include <string>

void Console::printBrain(int lineNum, OdomState state, string label) {
    label += (label.size() > 0 ? ": " : "");

    printBrain(lineNum, "%sx: %.3f y: %.3f theta: %.3f", label.c_str(), 
        state.x.convert(okapi::inch), 
        state.y.convert(okapi::inch), 
        state.theta.convert(okapi::degree)
    );
}

void Console::printBrain(int lineNum, QAngle ang, string label) {
    label += (label.size() > 0 ? ": " : "");

    printBrain(lineNum, "%s%.3f", label.c_str(), ang.convert(okapi::degree));
}

void Console::printBrain(int lineNum, QLength length, string label) {
    label += (label.size() > 0 ? ": " : "");

    printBrain(lineNum, "%s%.3f", label.c_str(), length.convert(okapi::inch));
}

void Console::printBrain(int lineNum, Point p, string label) {
    label += (label.size() > 0 ? ": " : "");

    printBrain(lineNum, "%sx: %.3f y: %.3f", label.c_str(), p.x.convert(okapi::inch), p.y.convert(okapi::inch));
}

void Console::printBrain(int lineNum, double n, string label) {
    label += (label.size() > 0 ? ": " : "");

    printBrain(lineNum, "%s%.3f", label.c_str(), n);
}

void Console::printBrain(int lineNum, bool n, string label) {
    label += (label.size() > 0 ? ": " : "");
    const char* boolStat = n ? "True" : "False";
    printBrain(lineNum, "%s%s", label.c_str(), boolStat);
}