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
    eff.slapper.move_voltage(12000*0.5);
    eff.smallerSlapper.move_velocity(-100*0.5);
    int count = 0;
    while (true) {  
        // original 200
        if (rot_sensor_val > 0 && count > 0) break; 
        if (rot_sensor_val < -6000 && count == 0) count++;

        pros::delay(5);
        rot_sensor_val = eff.rotSensorShooter.get_position();
        Console::printBrain(7, "Rot sensor shoot: %f", rot_sensor_val);
    }
    eff.slapper.move_velocity(0);
    eff.smallerSlapper.move_velocity(0);
}

void Routes::macro () {
    eff.rotSensorShooter.set_position(0);

    drive.setToleranceParams(nullopt, nullopt, 1.4_s);
    drive.goToPoint({-4_tile, -2_tile}, true, true, {{0, 1.4}});
    drive.resetToleranceParams();
    drive.moveTank(0, 0);
    // pros::delay(100);

    drive.moveArcade(-0.5, 0);
    pros::delay(600);
    drive.moveTank(0, -0.5);
    pros::delay(400);
    drive.moveTank(0, 0);

    drive.faceToPoint({-3_tile, 7_tile}, true, {{0, 0.7}});

    eff.toggleFourBar();
    pros::delay(300);
    eff.slapper.move_voltage(12000);
    eff.smallerSlapper.move_velocity(-100);
    pros::delay(41*1000);
    eff.slapper.move_voltage(0);
    eff.smallerSlapper.move_velocity(0);
    eff.toggleFourBar();

    // go back 
    
    // reset 
    
}

void Routes::skills () {
    OdomCustom::setPos(0_in, 0_in, -135_deg);

    macro();

    Task t (resetShooter);
    drive.faceToPoint({-2_tile, -3_tile}, true);
    
    drive.setToleranceParams(nullopt, nullopt, 1.3_s);
    drive.goBackward(1.2_tile, {{0, 1.3}});
    drive.resetToleranceParams();

    drive.faceToPoint({0_tile, -3_tile}, true);

    drive.setToleranceParams(nullopt, nullopt, 2.4_s);
    drive.goBackward(3_tile);
    drive.resetToleranceParams();

    drive.faceToPoint({30_tile, -45_tile}, true);

    drive.setToleranceParams(nullopt, nullopt, 1.4_s);
    drive.goBackward(19_in, {{0, 1.2}});
    drive.resetToleranceParams();


    drive.faceToPoint({50_tile, 0_tile}, true);
    drive.moveArcade(-1, 0);
    pros::delay(1200);

    drive.setToleranceParams(nullopt, nullopt, 1.2_s);
    drive.goForward(1.1_tile);
    drive.resetToleranceParams();
    drive.faceToPoint({3_tile, 3_tile}, true);

    drive.setToleranceParams(nullopt, nullopt, 2_s);
    drive.goBackward(2.2_tile);
    drive.resetToleranceParams();

    drive.faceToPoint({-1_tile, 3_tile}, true);
    
    eff.wingsToggle();
    drive.moveArcade(1, 0);
    pros::delay(1200);
    drive.moveArcade(0, 0);

    drive.moveArcade(-1, 0);
    pros::delay(600);
    drive.moveArcade(0, 0);
    eff.wingsToggle();
    
}