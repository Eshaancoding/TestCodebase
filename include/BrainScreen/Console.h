#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include "AutonSelector.h"
#include "main.h"
#include <memory>
#include <vector>
#include <string>
#include "display/lvgl.h"
#include "okapi/api/odometry/odomState.hpp"
#include "okapi/api/units/QSpeed.hpp"
using namespace std;

namespace Console {
    static unordered_map<int, lv_obj_t*> lines = {};

    // formatting the string giving args
    template<typename ... Args>
    std::string string_format( const std::string& format, Args ... args )
    {
        int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
        if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
        auto size = static_cast<size_t>( size_s );
        std::unique_ptr<char[]> buf( new char[ size ] );
        std::snprintf( buf.get(), size, format.c_str(), args ... );
        return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
    }

    // main function for printing
    template <typename... Arg>
    void printBrain(int lineNum, string str, Arg ...params) {
        string formattedStr = string_format(str, params...);

        // create lines if not exist;
        lv_obj_t* line;
        if (lines.find(lineNum) != lines.end()) {
            line = lines[lineNum];
        } else {
            line = lv_label_create(lv_scr_act(), NULL);  
            lv_label_set_long_mode(line, LV_LABEL_LONG_SCROLL);
            lv_obj_set_width(line, LV_HOR_RES);
            lv_obj_set_pos(line, 0, 5+lineNum*20);
            lines[lineNum] = line;
        }

        lv_label_set_text(line, formattedStr.c_str());
    }

    // helper functions for printing (will call the main printBrain function)
    // functions defined in PrintTypes.cpp
    void printBrain (int lineNum, OdomState state, string label="");
    void printBrain (int lineNum, QAngle ang, string label="");
    void printBrain (int lineNum, QLength length, string label="");
    void printBrain (int lineNum, Point p, string label="");
    void printBrain (int lineNum, double n, string label="");
};

#endif