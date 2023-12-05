#include "routes.h"

void Routes::skills () {
    eff.cataOne.move_velocity(100);
    eff.cataTwo.move_velocity(-100);
    pros::delay(10000); // how much delay?
    eff.cataOne.move_velocity(0);
    eff.cataTwo.move_velocity(0);

    eff.state = CataState::RESETTING;
    while (true) {
        eff.resetCata();
        if (eff.state == CataState::SHOOTING) { 
            break;
        }
        pros::delay(20);
    }
}