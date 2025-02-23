#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

// RELEASE MOGO 1 AFTER YOU GO MORE INWARDS TO YOU

void Routes::mogoSide () {

    //bool is_blue = (eff.isBlue).load();
    bool is_blue = false;

    // eff.toggleMogoMech();
    //eff.toggleBoinker();
    

    if (is_blue){
        OdomArc::setPos(0_in, 0_in, -88_deg); // set our default/initial position
        drive.goForward(1.7_tile);
    
    } else{
        OdomArc::setPos(0_in, 0_in, -90_deg); // set our default/initial position
        // drive.goPath({
        //     Path({0_tile, 0_tile}),
        //     Path({-1.7_tile, 0_tile}),
        //     Path({-2.2_tile, 0.2_tile})
        // }, 5_in, 5_in);
    };

    

    drive.goBackward(1.4_tile), {eff.toggleClamp()};
    //eff.toggleClamp();
    drive.turnLeft(90_deg);
    eff.setIntake(IntakeState::INTAKE);

    drive.goForward(1.1_tile);
    drive.turnLeft(180_deg);
    eff.toggleClamp();
    drive.goForward(1.8_tile);


 // get ready

 // OLD
    // eff.toggleMogoMech();

    // drive.setToleranceParams(0.5_s, 4_in);
    // is_blue ? drive.goBackward(0.4_tile) : drive.goBackward(0.3_tile);
    // drive.resetToleranceParams();
    
    // eff.toggleMogoMech(); // let go
    // //eff.toggleBoinker(); // let go


    // drive.setToleranceParams(0.75_s);
    // drive.turnLeft(170_deg);
    // drive.resetToleranceParams();
    // drive.goBackward(0.25_tile);
    // eff.toggleClamp(); // clamp mogo

    // eff.setIntake(IntakeState::INTAKE); // scored first ring
    // pros::delay(500);

    // drive.setToleranceParams(0.75_s);
    // is_blue? drive.turnLeft(90_deg, {{0, 0.9}}) : drive.turnLeft(90_deg);
    // drive.resetToleranceParams();

    // drive.goForward(is_blue ? 0.7_tile : 1.4_tile);
    // is_blue ? pros::delay(150) : pros::delay(125);
    // eff.setIntake(IntakeState::INACTIVE);
    // is_blue ? eff.toggleClamp() : drive.goBackward(0.4_tile); // unclamp
    // pros::delay(400);
    // if (is_blue){
    //     drive.turnRight(170_deg, {{0, 0.9}});
    //     drive.setToleranceParams(std::nullopt, 4_in);
    //     drive.goBackward(0.7_tile);
    //     drive.resetToleranceParams();
    // }
    // eff.toggleClamp(); // clamp mogo (if blue)
    // pros::delay(250);       

    // drive.setToleranceParams(0.75_s);
    // is_blue ? drive.turnRight(172_deg) : drive.turnLeft(45_deg);
    // drive.resetToleranceParams();
    // drive.setToleranceParams(std::nullopt, 4_in);
    // is_blue ? drive.goForward(0.7_tile) : drive.goBackward(1.1_tile);
    // drive.resetToleranceParams();
    // is_blue ? pros::delay(0) : eff.toggleClamp();
    // eff.setIntake(IntakeState::INTAKE); // score second ring on 2nd mogo
    // pros::delay(500);

    // // if qual touh ladder
    // if (!is_blue){
    //     drive.turnLeft(170_deg);
    //     drive.goForward(0.7_tile);
    // }
    // eff.setIntake(IntakeState::INACTIVE);


    //eff.toggleBoinker();
    // drive.goForward(1.65_tile);
    // drive.goBackward(0.55_tile);
    // eff.toggleBoinker();
    // drive.goBackward(0.3_tile);

    // drive.setToleranceParams(1_s);
    // drive.faceToPoint({-0.1_tile,-10.5_tile}, true);
    // drive.resetToleranceParams();
    
    // drive.setToleranceParams(std::nullopt, 4_in);
    // drive.goBackward(0.85_tile, {{0, 0.7}});
    // drive.resetToleranceParams();
    // pros::delay(300);
    // eff.toggleClamp(); // got the first mogo
    // eff.toggleIntakeState(INTAKE); // eat first donut
    // pros::delay(200);
    // drive.goForward(0.16_tile); // og 0.15
    // pros::delay(500);

    // eff.toggleIntakeState(SLOW);
    // drive.setToleranceParams(0.75_s);
    // is_blue ? drive.faceToPoint({20_tile, 0_tile}, true) : drive.faceToPoint({-20_tile, 0.1_tile}, true);
    // drive.setToleranceParams(0.5_s);
    // eff.toggleClamp(); // drop first mogo
    // drive.goForward(3.1_tile); // head towards mogo 2
    // drive.resetToleranceParams();
    // pros::delay(500);

    // eff.toggleIntakeState(INACTIVE); // grab dount 2
    // //drive.goBackward(0.52_tile); // go backwarde after grabbing donut
    
    
    // drive.setToleranceParams(1_s);
    // is_blue ? drive.turnRight(175_deg) : drive.turnRight(172_deg);
    // drive.setToleranceParams(0.5_s);
    // drive.goBackward(1.7_tile);
    // drive.resetToleranceParams();


    // eff.toggleClamp(); // clamp mogo 2
    // eff.toggleIntakeState(INTAKE);
    // pros::delay(1000);
    // drive.setToleranceParams(1_s);
    // is_blue ? drive.turnRight(175_deg) : drive.turnLeft(175_deg);

    // // turn the arm 
    // // eff.raiseArm();
    // // pros::delay(400);
    // // eff.stopArm();

    // // go forward and touch bar

    // drive.setToleranceParams(1.3_s);
    // drive.goForward(0.7_tile);
    // drive.resetToleranceParams();

    // eff.raiseArm();
    // pros::delay(500);
    // eff.stopArm();
    // eff.toggleIntakeState(INACTIVE);
    

}