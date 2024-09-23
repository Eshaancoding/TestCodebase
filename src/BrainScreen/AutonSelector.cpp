#include "AutonSelector.h"
#include "display/lv_conf.h"
#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_label.h"

namespace AutonSelector {
    bool selectedQualElim = false;
    bool selectedOffDef = false;

    bool isOffensive = false;
    bool isElim = false;
    bool shouldSkill = false;
    bool isDonePrompt = false;

    lv_obj_t* offensiveB;    
    lv_obj_t* defensiveB;    
    lv_obj_t* elimB;    
    lv_obj_t* qualB;    
    lv_obj_t* skillB;    
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

    lv_res_t setOffensive (lv_obj_t* obj) {
        isOffensive = true;
        selectedOffDef = true;
        lv_btn_set_state(defensiveB, LV_BTN_STATE_REL);
        lv_btn_set_state(skillB, LV_BTN_STATE_REL);

        return LV_RES_OK;
    }

    lv_res_t setDefensive (lv_obj_t* obj) {
        isOffensive = false;
        selectedOffDef = true;
        lv_btn_set_state(offensiveB, LV_BTN_STATE_REL);
        lv_btn_set_state(skillB, LV_BTN_STATE_REL);

        return LV_RES_OK;
    }

    lv_res_t setQual (lv_obj_t* obj) {
        isElim = false;
        selectedQualElim = true;
        lv_btn_set_state(elimB, LV_BTN_STATE_REL);
        lv_btn_set_state(skillB, LV_BTN_STATE_REL);

        return LV_RES_OK;
    }

    lv_res_t setElim (lv_obj_t* obj) {
        isElim = true;
        selectedQualElim = true;
        lv_btn_set_state(qualB, LV_BTN_STATE_REL);
        lv_btn_set_state(skillB, LV_BTN_STATE_REL);
        return LV_RES_OK;
    }

    lv_res_t setSkill (lv_obj_t* obj) {
        isOffensive = false;
        isElim = false;
        shouldSkill = true;
        lv_btn_set_state(qualB, LV_BTN_STATE_REL);
        lv_btn_set_state(elimB, LV_BTN_STATE_REL);
        lv_btn_set_state(offensiveB, LV_BTN_STATE_REL);
        lv_btn_set_state(defensiveB, LV_BTN_STATE_REL);
        selectedOffDef = false;
        selectedQualElim = false;

        return LV_RES_OK;
    }

    lv_res_t confirm (lv_obj_t* obj) {
        if (shouldSkill || (selectedOffDef && selectedQualElim)) {
            lv_obj_del(offensiveB);
            lv_obj_del(defensiveB);
            lv_obj_del(elimB);
            lv_obj_del(qualB);
            lv_obj_del(skillB);
            lv_obj_del(goButton);
            isDonePrompt = true;
        }

        return LV_RES_OK; 
    }

    State getState () { 
        return {
            isElim ? ELIM : QUAL, 
            isOffensive ? OFFENSIVE : DEFENSIVE, 
            !isDonePrompt ? NOTREADY : 
            shouldSkill ? SKILL : ROUTE
        };
    }

    void init () {
        shouldSkill = false;        

        offensiveB = createButton("Blue", 25, 25, 100, 50);
        defensiveB = createButton("Red", 150, 25, 100, 50);
        elimB = createButton("N/A", 25, 100, 100, 50);
        qualB = createButton("N/A", 150, 100, 100, 50);
        skillB = createButton("Skills", 25, 175, 225, 50);
        goButton = createButton("Confirm", 270, 175, 190, 50, false);

        // LV_IMG_DECLARE(logo);
        // lv_obj_t* img = lv_img_create(lv_scr_act(), NULL);
        // lv_img_set_src(img, &logo);

        lv_btn_set_action(offensiveB, LV_BTN_ACTION_CLICK, setOffensive);
        lv_btn_set_action(defensiveB, LV_BTN_ACTION_CLICK, setDefensive);
        lv_btn_set_action(elimB, LV_BTN_ACTION_CLICK, setElim);
        lv_btn_set_action(qualB, LV_BTN_ACTION_CLICK, setQual);
        lv_btn_set_action(skillB, LV_BTN_ACTION_CLICK, setSkill);
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
