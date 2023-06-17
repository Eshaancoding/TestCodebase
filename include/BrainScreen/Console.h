#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include "AutonSelector.h"
#include <memory>
#include <vector>
#include <string>
#include "display/lvgl.h"
using namespace std;

namespace Console {
    static vector<lv_obj_t*> lines = {};

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


    template <typename... Arg>
    void printBrain(int lineNum, string str, Arg ...params) {
        if (AutonSelector::getState().status == AutonSelector::NOTREADY) return;

        string formattedStr = string_format(str, params...);

        // create lines if not exist;
        while (lineNum >= lines.size()) {
            lv_obj_t* label = lv_label_create(lv_scr_act(), NULL);  
            lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL);
            lv_obj_set_width(label, LV_HOR_RES);
            lv_obj_set_pos(label, 0, 5+lines.size()*20);
            lines.push_back(label);
        }

        lv_label_set_text(lines[lineNum], formattedStr.c_str());
    }
};

#endif