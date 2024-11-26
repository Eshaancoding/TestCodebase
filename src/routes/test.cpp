// 4 PID ignore
#include "Console.h"
#include "MovingAverage.h"
#include "drive.h"
#include "Odom/Math.h"
#include "okapi/api/odometry/odomState.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QTime.hpp"
#include "parameters.h"
#include "pros/adi.h"
#include "effectors.h"
#include "odom/OdomCustom.h"
#include "PIDParams.h"

void help(double distance){
    //initialize motors
    pros::Motor rightF;
    pros::Motor rightB;
    pros::Motor leftF;
    pros::Motor leftB;

    double motorDia = 5;
    rightF.set_zero_position(0); // reset encoder

    distance = (distance/motorDia)*360; // convert distance to degrees
    double error = distance - rightF.get_position();

    // PID params: p , i, d, maxPower, minPower, factor, minErrThreshold, slew
    PID p = PID(0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1); // pid for path
    PID h = PID(0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1); // pid for heading

    double factor = p.step(error); // get factor
    double heading = OdomCustom::angleGet(); // get current angle
    double hfactor = h.step(heading); // get factor for heading

    while(error>0){
        leftF.move_velocity(factor*200 + hfactor*200);
        leftB.move_velocity(factor*200 + hfactor*200);
        
        rightF.move_velocity(factor*200 - hfactor*200);
        rightB.move_velocity(factor*200 - hfactor*200);
        
        /*
        rightF.move_velocity(factor*200);
        rightB.move_velocity(factor*200); 
        leftF.move_velocity(factor*200); 
        leftB.move_velocity(factor*200);

        if (heading>0){
            rightF.move_velocity(hfactor*200);
            rightB.move_velocity(hfactor*200);
        } else if (heading<0) {
            leftF.move_velocity(hfactor*200);
            leftB.move_velocity(hfactor*200);
        }
        */

        //drive.moveArcade(200*factor, 200*hfactor);

        heading = OdomCustom::angleGet();
        hfactor = h.step(heading);
        error = distance - rightF.get_position();
        factor = p.step(error);
    }


}

