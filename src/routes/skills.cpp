// #include "main.h"
// #include "pros/misc.h"
// #include "pros/rtos.h"
// #include "parameters.h"
// #include "pros/screen.h"
// #include "routes.h"
// #include "drive.h"
// #include "effectors.h"
// #include "Console.h"
// #include "odom/OdomCustom.h"
// #include "odom/Math.h"
// #include "AutonSelector.h"
// #include "controller.h"

// void resetShooter () {
//     double rot_sensor_val = eff.rotSensorShooter.get_position();
//     eff.slapper.move_voltage(12000);
//     eff.smallerSlapper.move_velocity(-100);
//     int count = 0;
//     while (true) {  
//         // original 200
//         if (abs(rot_sensor_val) < 100 && count > 0) break; 
//         if (rot_sensor_val < -6000 && count == 0) count++;

//         pros::delay(3);
//         rot_sensor_val = eff.rotSensorShooter.get_position();
//     }
//     eff.slapper.move_velocity(0);
//     eff.smallerSlapper.move_velocity(0);
// }

// void Routes::macro (bool run_shooter, bool manual_stop) {
//     OdomCustom::setPos(0_in, 0_in, -135_deg);
//     eff.isDriveReverse = true;
//     eff.rotSensorShooter.set_position(0);

//     drive.moveArcade(1, 0.45);
//     pros::delay(800);
//     eff.setIntake(true, false); // reverse intake
//     pros::delay(400);
//     drive.moveTank(-0.2, -0.75);
//     pros::delay(650);
//     drive.moveArcade(0.1, 0);
//     pros::delay(300);
//     drive.moveArcade(0, 0);
//     eff.setIntake(false, true); // turn off

//     drive.setToleranceParams(nullopt, 0.5_deg, 2_s);
//     drive.faceToPoint({-2.75_tile, 6_tile}, true);
//     drive.resetToleranceParams();

//     eff.wingsPistonRight.set_value(1);
//     if (run_shooter) {
//         eff.slapper.move_voltage(12000);
//         eff.smallerSlapper.move_voltage(-12000);
//         auto start = pros::millis();

//         int duration = manual_stop ? 25 : 22; // seconds

//         while (pros::millis() - start <= duration * 1000) {
//             if (manual_stop && Control::getDebouncePressed(pros::E_CONTROLLER_DIGITAL_UP))
//                 break;
//             pros::delay(25);
//         }
//         eff.slapper.move_voltage(0);
//         eff.smallerSlapper.move_voltage(0);
//     }
//     eff.wingsPistonRight.set_value(0);

// }

// void Routes::skills () {

//     macro();

//     // ===================== Go under ==============
//     drive.goForward(4_in);
//     drive.faceToPoint({-30_tile, -30_tile}, true);

//     OdomCustom::setPos(0_in, 0_in, -135_deg);
//     drive.goPath({
//         Path({0_in, 0_in}),
//         Path({0.5_tile, 0.5_tile}),
//         Path({0.53_tile, 1_tile}, 0.4, 1.4),
//         Path({0.53_tile, 4_tile}),
//         Path({-0.4_tile, 5_tile}),
//     }, 8_in, 10_in, true);

//     // ==================== The rest of the slam movement ===========

//     drive.moveArcade(0.5, 0);
//     pros::delay(200);
//     drive.faceToPoint({-10_tile, 0_tile}, true);
//     drive.moveArcade(-1, 0);
//     pros::delay(400);
//     drive.moveArcade(0.5, 0);
//     pros::delay(200);
//     drive.moveArcade(0, 0);
//     drive.faceToPoint({-0_tile, 10_tile}, true);

//     drive.goPath({
//         Path({0_in, 0_in}, 1, 0.8, 0.3_tile),
//         Path({0_in, -1.2_tile}, 1, 0.8, 0.3_tile, [](){
//             eff.wingsPistonRight.set_value(1);
//         }),
//         Path({0_in, -1.35_tile}, 1, 0.8, 0.3_tile, [](){
//             eff.wingsPistonLeft.set_value(1);
//         }),
//         Path({-0.5_tile, -1.65_tile}, 1, 0.8, 0.3_tile),
//         Path({-0.85_tile, -1.73_tile}, 1, 0.8, 0.3_tile),
//         Path({-1.2_tile, -1.8_tile}, 1, 0.8, 0.3_tile)
//     }, 8_in, 6_in, true, 4.5_s);

//     eff.wingsPistonRight.set_value(0);
//     drive.faceToPoint({15_tile, -40_tile}, true, {{0, 1.3}});
//     eff.wingsPistonRight.set_value(1);
//     drive.moveArcade(-0.7, 0);
//     pros::delay(1200);
//     drive.moveArcade(1, 0);
//     pros::delay(400);
//     drive.moveArcade(-1, 0);
//     pros::delay(600);
//     drive.moveArcade(0.5, 0);
//     pros::delay(300);
//     drive.moveArcade(0, 0);

//     // ============== Right ==============
//     eff.wingsPistonLeft.set_value(0);
//     eff.wingsPistonRight.set_value(0);
//     drive.goPath({
//         Path({0_in, 0_in}),
//         Path({0_in, -0.8_tile}),
//         Path({-1.3_tile, -0.8_tile}),
//     }, 8_in, 6_in, false, 4_s);

//     drive.faceToPoint({-30_tile, -50_tile}, true, {{0, 1.3}});
    
//     eff.wingsPistonLeft.set_value(1);
//     eff.wingsPistonRight.set_value(1);
//     drive.moveArcade(-1, 0);
//     pros::delay(1200);
//     drive.moveArcade(0, 0);
//     eff.wingsPistonLeft.set_value(0);
//     eff.wingsPistonRight.set_value(0);

//     // ============== very Right ==============
//     OdomCustom::setPos(0_in, 0_in, -180_deg);
    
//     drive.goForward(1_tile);

//     drive.setToleranceParams(nullopt, nullopt, 0.5_s);
//     drive.faceToPoint({30_tile, -10_tile}, true);
//     drive.resetToleranceParams();
    
//     eff.wingsPistonLeft.set_value(1);
//     drive.goPath({
//         Path({0_in, 0_in}, 0.4, 1.2),
//         Path({-1.65_tile, 1_tile}),
//         Path({-1.65_tile, 1.5_tile}),
//         Path({-1.5_tile, 1.75_tile}),
//     }, 8_in, 12_in, true, 5_s);

//     drive.faceToPoint({-40_tile, -30_tile}, true, {{0, 1.3}});
//     eff.wingsPistonLeft.set_value(0);
//     drive.moveArcade(0.5, 0);
//     pros::delay(200);
//     drive.moveArcade(-1, -0.3);
//     pros::delay(1200);
//     drive.moveArcade(1, 0.5);
//     pros::delay(500);
//     drive.moveArcade(0, 0);
    
// }