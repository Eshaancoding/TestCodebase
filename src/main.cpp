#include "main.h"
#include "OdomMath.h"
#include "LVGL/LVGL.h"
#include "display/lv_core/lv_obj.h"

void disabled() {}
void competition_initialize() {}

// When robot initializes. 
void initialize() {
	// pros::lcd::initialize(); 

    auto btn = ToggleButton(
        "test",
        0, 0, 
        100,
        50,
        [](lv_obj_t* obj) -> lv_res_t {
            printf("calling func\n");
            auto currentButton = (ToggleButton*)lv_obj_get_free_ptr(obj);

            if (currentButton == nullptr) {
                printf("Current button null\n");
            } else {
                printf("Current button not null... executing\n");
                currentButton->setPos(200);
            }

            
            return LV_RES_OK;
        }
    );

    btn.render();

}


// Autonomous Mode
void autonomous() {

};

// Operation control (driver)
void opcontrol() {

	Point point = Math::findPointOffset(
		{0_in, 1_in, 180_deg}	
	, 3_in);

	printf("P: %f %f\n", point.x.convert(inch), point.y.convert(inch));
}
