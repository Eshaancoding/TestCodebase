#include "routes.h"
#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomCustom.h"

void Routes::macro () {
    drive.setToleranceParams(nullopt, nullopt, 1.4_s);
    drive.goToPoint({-4_tile, -2_tile}, true, true, {{0, 1.4}}); // 0.7
    drive.resetToleranceParams();
    drive.moveTank(0, 0);
    // pros::delay(100);

    // // move one motor side
    drive.moveTank(0, -0.65);
    pros::delay(650);
    drive.moveTank(0, 0);

    drive.faceToPoint({-2.5_tile, 6_tile}, true, {{0, 0.7}});

    // eff.toggleFourBar();
    // eff.slapper.move_voltage(12000);
    // eff.smallerSlapper.move_velocity(-100);
    // pros::delay(41*1000);
    // eff.slapper.move_voltage(0);
    // eff.smallerSlapper.move_velocity(0);
    // eff.toggleFourBar();

    // go back 
    
    // reset 
    double rot_sensor_val = eff.rotSensorShooter.get_position();
    eff.slapper.move_voltage(12000*0.5);
    eff.smallerSlapper.move_velocity(-100*0.5);
    pros::delay(100);
    eff.rotSensorShooter.set_position(0);
    while (rot_sensor_val <= 7700) { 
        pros::delay(10);
        rot_sensor_val = eff.rotSensorShooter.get_position();
        Console::printBrain(7, "Rot sensor shoot: %f", rot_sensor_val);
    }
    eff.slapper.move_velocity(0);
    eff.smallerSlapper.move_velocity(0);
}

void Routes::skills () {
    OdomCustom::setPos(0_in, 0_in, -135_deg);

    macro();

    pros::delay(200);

    drive.moveArcade(1,0);
    pros::delay(100);
    drive.moveArcade(0,0);
    drive.faceToPoint({-3_tile, -3_tile}, true, {{0, 0.7}});
    drive.moveArcade(-1,0);
    pros::delay(600);
    drive.moveArcade(0, 0);
    drive.faceToPoint({0_tile, -3_tile}, true, {{0, 0.7}});
    drive.moveArcade(-1, 0);
    pros::delay(1500);
    drive.moveArcade(0,0);
    drive.faceToPoint({3_tile, -3_tile}, true, {{0, 0.7}});
    drive.moveArcade(-1, 0);
    pros::delay(300);
    drive.moveArcade(1, 0);
    pros::delay(300);

    // going to middle
    // eff.setIntake(true, false);
    // drive.moveArcade(1, 0);
    // pros::delay(1700);
    // pros::delay(300);
    // drive.moveArcade(0, 0);
    // pros::delay(50);


    // we are over 
    // drive.faceToPoint({-20_tile, 30_tile}, true);
    
    // eff.wingsToggle();

    // drive.moveArcade(1, 0);
    // pros::delay(900);
    // drive.goBackward(1_tile);
    // drive.moveArcade(1, 0);
    // pros::delay(800);
    // drive.moveArcade(0, 0);
    // eff.setIntake(false, false);

    // drive.turnLeft(45_deg);

    // drive.faceToPoint({-20_tile, -20_tile}, true);
    // drive.goBackward(19_in);
    // drive.turnLeft(45_deg);
    // drive.goBackward(19_in);

    
    // drive.faceToPoint({-10_tile, -10_tile}, true);
    // drive.goBackward(12_in);
    // drive.faceToPoint({-5_tile, 50_tile}, true);

    // drive.setToleranceParams(nullopt, nullopt, 1_s);
    // drive.goBackward(8_in, {{0, 1.4}});
    // drive.resetToleranceParams();

    // // move left side back
    // drive.moveTank(-0.5, 0);
    // pros::delay(600);
    // drive.moveTank(0, 0);

    // eff.toggleShootingState();
    // while (true) {
    //     eff.stepShootMotor();
    //     pros::delay(50);
    // }
}