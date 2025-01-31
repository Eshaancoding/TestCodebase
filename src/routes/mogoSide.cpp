#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

void Routes::mogoSide () {

    OdomArc::setPos(0_in, 0_in, 1_deg); // set our default/initial position

    eff.toggleBoinker();
    drive.goForward(1.63_tile);
    drive.goBackward(0.55_tile);
    eff.toggleBoinker();
    drive.goBackward(0.3_tile);

    drive.setToleranceParams(1_s);
    drive.faceToPoint({-0.3_tile,-10.5_tile}, true);
    drive.resetToleranceParams();
    
    drive.goBackward(0.85_tile);
    eff.toggleClamp(); // got the first mogo
    eff.toggleIntakeState(INTAKE); // eat first donut
    pros::delay(1000);
    eff.toggleClamp(); // drop first mogo


    drive.setToleranceParams(0.75_s);
    drive.turnLeft(85_deg);
    drive.setToleranceParams(0.5_s);
    eff.toggleIntakeState(SLOW);
    drive.goForward(0.98_tile); // head towards mogo 2
    drive.resetToleranceParams();
    pros::delay(325);

    eff.toggleIntakeState(INACTIVE); // grab dount 2
    drive.goBackward(0.5_tile); // go backwarde after grabbing donut
    
    
    drive.setToleranceParams(1_s);
    drive.turnRight(175_deg);
    drive.setToleranceParams(0.5_s);
    drive.goBackward(1.05_tile);
    drive.resetToleranceParams();


    eff.toggleClamp(); 
    eff.toggleIntakeState(INTAKE);
    pros::delay(1000);
    drive.setToleranceParams(1_s);
    drive.turnRight(175_deg);

    // turn the arm 
    eff.raiseArm();
    pros::delay(400);
    eff.stopArm();

    // go forward and touch bar

    drive.setToleranceParams(1.3_s);
    drive.goForward(0.6_tile);
    drive.resetToleranceParams();
    eff.toggleClamp(); // unclamp
    eff.toggleIntakeState(INACTIVE);

}