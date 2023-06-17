#include "LVGL/LVGL.h"
#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_btn.h"
#include "display/lv_objx/lv_btnm.h"

void ToggleButton :: render () {
    obj = lv_btn_create(lv_scr_act(), NULL);
    lv_btn_set_toggle(obj, true);
    lv_obj_set_pos(obj, x, y);                            /*Set its position*/
    lv_obj_set_size(obj, w, h);                          /*Set its size*/

    label = lv_label_create(obj, NULL);          /*Add a label to the button*/
    lv_label_set_text(label, name.c_str());
    lv_btn_set_action(obj, LV_BTN_ACTION_CLICK, func);
    lv_obj_set_free_ptr(obj, this);
}

void ToggleButton :: derender () {
    printf("derending \n");
    lv_obj_del(obj);
    lv_obj_del(label);
}

void ToggleButton :: setText (string newText) {
    name = newText;
    lv_label_set_text(label, name.c_str());                     
}

void ToggleButton :: setPos (int newX, int newY) {
    int newCoordX = newX > -1 ? newX : x;
    int newCoordY = newY > -1 ? newY : x;

    x = newCoordX; y = newCoordY;
    
    lv_obj_set_pos(obj, x, y);
}

void ToggleButton :: setSize (int newW, int newH) {
    int newDimW = newW > -1 ? newH : x;
    int newDimH = newH > -1 ? newH : x;

    w = newDimW; h = newDimH;
    
    lv_obj_set_size(obj, w, h);
}