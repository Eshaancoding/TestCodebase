#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.h"
#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"
#include "odom/Math.h"
#include "AutonSelector.h"
#include "controller.h"

void resetShooter () {
    double rot_sensor_val = eff.rotSensorShooter.get_position();
    eff.slapper.move_voltage(12000);
    eff.smallerSlapper.move_velocity(-100);
    int count = 0;
    while (true) {  
        // original 200
        if (abs(rot_sensor_val) < 100 && count > 0) break; 
        if (rot_sensor_val < -6000 && count == 0) count++;

        pros::delay(3);
        rot_sensor_val = eff.rotSensorShooter.get_position();
    }
    eff.slapper.move_velocity(0);
    eff.smallerSlapper.move_velocity(0);
}

void Routes::macro () {
    OdomCustom::setPos(0_in, 0_in, -135_deg);
    eff.rotSensorShooter.set_position(0);

    drive.moveArcade(1, 0.4);
    pros::delay(800);
    eff.setIntake(true, false); // reverse intake
    pros::delay(400);
    drive.moveTank(-0.2, -0.8);
    pros::delay(800);
    drive.moveArcade(0, 0);

    pros::delay(1000);

    eff.setIntake(false, true); // turn off
}

void Routes::skills () {

    macro();

    drive.goForward(4_in);
    drive.faceToPoint({-30_tile, -30_tile}, true);

    OdomCustom::setPos(0_in, 0_in, -135_deg);
    drive.goPath({
        Path({0_in, 0_in}),
        Path({0.5_tile, 0.5_tile}),
        Path({0.53_tile, 1_tile}, 0.4, 1.4),
        Path({0.53_tile, 3.7_tile}),
        Path({-0.4_tile, 4.7_tile}),
    }, 8_in, 6_in, true);

    drive.moveArcade(-1, 0);
    pros::delay(1000);
    drive.moveArcade(0, 0);

    // curved path (this is for hitting triball)
    OdomCustom::setPos(0_in, 0_in, 90_deg);
    drive.goPath({
        Path({0_tile, 0_tile}),
        Path({0.4_tile, 0_tile}),
        Path({0.6_tile, -0.3_tile}),
        Path({0_tile, -1_tile}),
        Path({-0.5_tile, -1.3_tile}, 1.5, 0.5),
        Path({-0.5_tile, -0.9_tile}, 0.5, 1.5),
        Path({-0.5_tile, -0.3_tile}, 0.5, 1.5),
    }, 5_in, 2_in);
    
}