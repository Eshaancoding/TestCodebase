#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

//ringside rush
void Routes::ringSide () {
    OdomArc::setPos(0_in, 0_in, 0_deg); // set our default/initial position

    eff.toggleBoinker();
    drive.goPath({ // turn towards 4 stack ring
        Path({0_tile,0_tile}),
        Path({-0.1_tile,2.2_tile}),
        Path({0.3_tile,2_tile})
    }); 
    drive.faceToPoint({1.5_tile,1_tile},true); // face mogo
    drive.goBackward(1.17_tile); // go back towards mogo
    eff.toggleClamp(); // clmap mogo
    drive.turnRight(45_deg); // turn towards rings
    eff.toggleBoinker(); // let go of first 4 stack ring
    eff.toggleIntakeState(INTAKE); // intake
    drive.goForward(1.5_tile); // intake both rings
    drive.faceToPoint({0_tile,-2_tile}, true); // turn towards ladder
    drive.goForward(2_tile); // touch ladder
    eff.toggleClamp();
   
}