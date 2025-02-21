#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"   

//ringside rush
void Routes::test () {
    OdomArc::setPos(0_tile, 2_tile, 90_deg);
    // eff.setIntake(IntakeState::INTAKE);

    // eff.toggleClamp();

}

