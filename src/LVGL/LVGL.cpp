#include "LVGL/LVGL.h"
#include "display/lv_conf.h"

void View :: derender () {
    for (Button but : buttons) {
        but.derender();    
    }
    for (Text text : texts) {
        text.derender();    
    }
}

void View :: render () {
    for (Button but : buttons) {
        but.render();    
    }
    for (Text text : texts) {
        text.render();    
    }
}

void Button :: render () {
        
}