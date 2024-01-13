#include "AutonSelector.h"
#include "display/lv_conf.h"
#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_label.h"

namespace AutonSelector {
    bool selectedSide = false;
    bool selectedRisky = false;

    bool isRisky = false;
    bool isLeft = false;
    bool shouldTest = true;
    bool isDonePrompt = false;

    lv_obj_t* leftButton;    
    lv_obj_t* rightButton;    
    lv_obj_t* riskyButton;    
    lv_obj_t* nonRiskyButton;    
    lv_obj_t* testButton;    
    lv_obj_t* goButton;    


    lv_obj_t* createButton(string name, int x, int y, int w, int h, bool setToggle=true) {
        lv_obj_t* obj = lv_btn_create(lv_scr_act(), NULL);
        lv_btn_set_toggle(obj, setToggle);
        lv_obj_set_pos(obj, x, y);                            /*Set its position*/
        lv_obj_set_size(obj, w, h);                          /*Set its size*/


        lv_obj_t* label = lv_label_create(obj, NULL);          /*Add a label to the button*/
        lv_label_set_text(label, name.c_str());

        return obj;
    }

    lv_res_t setLeft (lv_obj_t* obj) {
        isLeft = true;
        selectedSide = true;
        lv_btn_set_state(rightButton, LV_BTN_STATE_REL);
        lv_btn_set_state(testButton, LV_BTN_STATE_REL);

        return LV_RES_OK;
    }

    lv_res_t setRight (lv_obj_t* obj) {
        isLeft = false;
        selectedSide = true;
        lv_btn_set_state(leftButton, LV_BTN_STATE_REL);
        lv_btn_set_state(testButton, LV_BTN_STATE_REL);

        return LV_RES_OK;
    }

    lv_res_t setRiskyFalse (lv_obj_t* obj) {
        isRisky = false;
        selectedRisky = true;
        lv_btn_set_state(riskyButton, LV_BTN_STATE_REL);
        lv_btn_set_state(testButton, LV_BTN_STATE_REL);

        return LV_RES_OK;
    }

    lv_res_t setRiskyTrue (lv_obj_t* obj) {
        isRisky = true;
        selectedRisky = true;
        lv_btn_set_state(nonRiskyButton, LV_BTN_STATE_REL);
        lv_btn_set_state(testButton, LV_BTN_STATE_REL);
        return LV_RES_OK;
    }

    lv_res_t setTest (lv_obj_t* obj) {
        isRisky = !isRisky;
        shouldTest = true;
        lv_btn_set_state(nonRiskyButton, LV_BTN_STATE_REL);
        lv_btn_set_state(riskyButton, LV_BTN_STATE_REL);
        lv_btn_set_state(leftButton, LV_BTN_STATE_REL);
        lv_btn_set_state(rightButton, LV_BTN_STATE_REL);
        selectedRisky = false;
        selectedSide = false;

        return LV_RES_OK;
    }

    lv_res_t confirm (lv_obj_t* obj) {
        if (shouldTest || (selectedRisky && selectedSide)) {
            lv_obj_del(leftButton);
            lv_obj_del(rightButton);
            lv_obj_del(riskyButton);
            lv_obj_del(nonRiskyButton);
            lv_obj_del(testButton);
            lv_obj_del(goButton);
            isDonePrompt = true;
        }

        return LV_RES_OK; 
    }

    State getState () { 
        return {
            isLeft ? ELIM : QUAL, 
            isRisky ? OFFENSIVE : DEFENSIVE, 
            !isDonePrompt ? NOTREADY : 
            shouldTest ? TEST : ROUTE
        };
    }

    void init () {
        shouldTest = false;        

        leftButton = createButton("Off", 25, 25, 100, 50);
        rightButton = createButton("Def", 150, 25, 100, 50);
        riskyButton = createButton("Elim", 25, 100, 100, 50);
        nonRiskyButton = createButton("Qual", 150, 100, 100, 50);
        testButton = createButton("Skill", 25, 175, 225, 50);
        goButton = createButton("Confirm", 270, 175, 190, 50, false);

        // LV_IMG_DECLARE(logo);

        // lv_obj_t* img = lv_img_create(lv_scr_act(), NULL);
        // lv_img_set_src(img, &logo);

        lv_btn_set_action(leftButton, LV_BTN_ACTION_CLICK, setLeft);
        lv_btn_set_action(rightButton, LV_BTN_ACTION_CLICK, setRight);
        lv_btn_set_action(riskyButton, LV_BTN_ACTION_CLICK, setRiskyTrue);
        lv_btn_set_action(nonRiskyButton, LV_BTN_ACTION_CLICK, setRiskyFalse);
        lv_btn_set_action(testButton, LV_BTN_ACTION_CLICK, setTest);
        lv_btn_set_action(goButton, LV_BTN_ACTION_CLICK, confirm);

        // set style the go button
        lv_style_t* style = lv_btn_get_style(goButton, LV_BTN_STYLE_PR);
        style->body.radius = 35;
        lv_btn_set_style(goButton, LV_BTN_STYLE_PR, style);

        lv_style_t* newStyle = lv_btn_get_style(goButton, LV_BTN_STYLE_REL);
        newStyle->body.radius = 35;
        lv_btn_set_style(goButton, LV_BTN_STYLE_REL, newStyle);
    } 
}
