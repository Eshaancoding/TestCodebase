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
        Console::printBrain(7, "Rot sensor shoot: %f", rot_sensor_val);
    }
    eff.slapper.move_velocity(0);
    eff.smallerSlapper.move_velocity(0);
}

void Routes::macro () {
    OdomCustom::setPos(0_in, 0_in, -135_deg);
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

    drive.faceToPoint({-35_tile, 70_tile}, true, {{0, 0.7}});

    eff.toggleFourBar();
    pros::delay(300);
    eff.slapper.move_voltage(12000);
    eff.smallerSlapper.move_velocity(-100);
    pros::delay(1*1000); // CAHBGEN TO 41
    eff.slapper.move_voltage(0);
    eff.smallerSlapper.move_velocity(0);
    eff.toggleFourBar();

    // go back 
    // reset 
    
}

void Routes::skills () {

    macro();

    Task t (resetShooter);
    drive.faceToPoint({2_tile, 3_tile}, true);
    
    drive.setToleranceParams(nullopt, nullopt, 1.3_s);
    drive.goForward(0.9_tile, {{0, 1}}); // THIS THIS HTHIS THIS 
    drive.resetToleranceParams();

    drive.faceToPoint({0_tile, 3_tile}, true);

    drive.setToleranceParams(nullopt, nullopt, 2.35_s);
    drive.goForward(3.0_tile, { 
        {0, 0.7},
        {0.6, 1}
    });
    drive.resetToleranceParams();

    drive.setToleranceParams(nullopt, nullopt, 2.1_s, 0.8);
    // curve movement to hit triball
    drive.goToPoint({-6_tile, 4_tile}, true, true, {{0, 1.4}});
    drive.resetToleranceParams();

    // go backwardo
    drive.goBackward(0.6_tile);

    // face the point of interest to go the center
    drive.faceToPoint({-20_tile, -30_tile}, true);

    // actually go the center
    drive.setToleranceParams(nullopt, nullopt, 2_s);
    drive.goForward(2_tile);
    drive.resetToleranceParams();

    // face the actual point
    drive.faceToPoint({-20_tile, 30_tile}, true);
    
    // go back and forth and back and forth and back and forth
    eff.wingsToggle();
    drive.moveArcade(1, 0);
    pros::delay(900);
    drive.moveArcade(-1, 0);
    pros::delay(500);
    drive.moveArcade(1, 0);
    pros::delay(700);
    drive.moveArcade(-1, 0);
    pros::delay(500);
    drive.moveArcade(0, 0);
    
}