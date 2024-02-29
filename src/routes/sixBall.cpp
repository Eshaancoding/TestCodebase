#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::sixBall () {
    OdomCustom::setPos(0_in, 0_in, 15_deg);
    
    // =========== match triball go away =========== 
    eff.setIntake(true, false);
    pros::delay(700);
    eff.setIntake(false, true);

    // =========== go to mid =========== 
    drive.goPath({
        Path({0_in, 0_in}),
        Path({-2_tile, -2_tile})
    }, 8_in, 3_in);

    // =========== slam at mid =========== 
    drive.faceToPoint({0_tile, 10_tile}, true);
    drive.moveArcade(1, 0);
    pros::delay(1200);
    drive.moveArcade(1, 0);

    // =========== get the triball on right =========== 
    drive.goPath({
        Path({0_in, 0_in}),
        Path({0.5_tile, -1_tile})
    }, 4_in, 3_in, true);

    drive.turnRight(180_deg);

    eff.setIntake(); 
    drive.goForward(0.8_tile);

    // =========== curve movement to the right side =========== 
    // ================ and get triball =======================
    drive.goPath({
        Path({0_in, 0_in}), 
        Path({1_tile, 2_tile}),
        Path({1.5_tile, 1_tile}, 1, 1, 0.3_tile),
    }, 8_in, 3_in, true);

    eff.setIntake(true, false);
    pros::delay(500);
    eff.setIntake();
    
    drive.faceToPoint({0_in, -10_tile}, true);
    drive.goForward(1_tile);

    // ===== last movement to get all triballs under goal =====
    drive.goPath({
        Path({0_in, 0_in}),
        Path({0_in, 1.75_tile}),
        Path({-1_tile, 3_tile}),
    }, 8_in, 7_in, true);

    drive.moveArcade(-1, 0);
    pros::delay(1200);
    drive.moveArcade(0.6, 0);
    pros::delay(200);
    drive.moveArcade(0, 0);

    drive.turnRight(180_deg);
    drive.moveArcade(1, 0);
    pros::delay(1000);
    drive.moveArcade(-1, 0);
    pros::delay(600);
    drive.moveArcade(0, 0);


}
