#include "LVGL/LVGL.h"

void View :: derender () {
    for (ToggleButton but : buttons) {
        but.derender();    
    }
    for (Text text : texts) {
        text.derender();    
    }
}

void View :: render () {
    for (ToggleButton but : buttons) {
        but.render();    
    }
    for (Text text : texts) {
        text.render();    
    }
}