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

void Routes::macro (bool run_shooter) {
    OdomCustom::setPos(0_in, 0_in, -135_deg);
    eff.rotSensorShooter.set_position(0);

    drive.moveArcade(1, 0.4);
    pros::delay(800);
    eff.setIntake(true, false); // reverse intake
    pros::delay(400);
    drive.moveTank(-0.2, -0.8);
    pros::delay(800);
    drive.moveArcade(0, 0);
    eff.setIntake(false, true); // turn off
    drive.faceToPoint({-1.25_tile, 6_tile}, true);

    if (run_shooter) {
        eff.slapper.move_voltage(12000);
        eff.smallerSlapper.move_voltage(-12000);
        pros::delay(27 * 1000);
        eff.slapper.move_voltage(0);
        eff.smallerSlapper.move_voltage(0);
    }
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
        Path({0.53_tile, 4_tile}),
        Path({-0.4_tile, 5_tile}),
    }, 8_in, 10_in, true);

    drive.moveArcade(-1, 0);
    pros::delay(1000);
    drive.moveArcade(0.7, 0);
    pros::delay(250);
    drive.faceToPoint({20_tile, -5_tile}, true);
    drive.moveArcade(-1, 0);
    pros::delay(1000);
    drive.moveArcade(0, 0);

    // curved path (this is for hitting triball)
    OdomCustom::setPos(0_in, 0_in);
    drive.goPath({
        Path({0_tile, 0_tile}, 1, 0.8, 0.3_tile),
        Path({0.4_tile, -0.4_tile}, 1, 0.8, 0.3_tile),
        Path({0_tile, -0.8_tile}),
        Path({-2_tile, -1.75_tile})
    }, 8_in, 6_in);

    drive.setToleranceParams(nullopt, nullopt, 0.75_s);
    drive.faceToPoint({0_tile, 20_tile}, true);
    drive.resetToleranceParams();

    // slam
    eff.wingsToggle();
    drive.moveArcade(1, 0);
    pros::delay(1200);
    drive.moveArcade(-1, 0);
    pros::delay(600);
    drive.moveArcade(1, 0);
    pros::delay(1000);
    drive.moveArcade(-1, 0);
    pros::delay(600);
    drive.moveArcade(0, 0);
    eff.wingsToggle();
    
}