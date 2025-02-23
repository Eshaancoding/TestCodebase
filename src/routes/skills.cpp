#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"
#include "odom/OdomArc.h"
#include <optional>

void Routes::skills () {

	OdomArc::setPos(0_tile, 2_tile, 45_deg);
    
    eff.raiseArm();
    pros::delay(850);
    eff.currentState = State::IDLE;
    eff.arm_state = ArmState::PID_ARM;

    drive.goBackward(0.5_tile);

    eff.toggleClamp();
    drive.turnRight(130_deg);
    eff.setIntake(IntakeState::INTAKE);
    drive.goForward(1.2_tile);

    drive.turnRight(90_deg);

    drive.goForward(1_tile);
    // drive.turnLeft(90_deg); // 90 deg left turn
    auto p = OdomArc::getPos();
    drive.faceToPoint({p.x + 0_tile, p.y - 3_tile});

    eff.arm_state = ArmState::PID_ARM;
    eff.changeState();
    drive.goForward(1_tile);
    eff.setIntake(IntakeState::INACTIVE);

    drive.turnRight(90_deg);
    drive.goForward(0.25_tile);
    eff.changeState();
    pros::delay(500);
    eff.changeState();

    drive.goBackward(0.25_tile);

    // drive.turnRight(90_deg);
    // eff.setIntake(IntakeState::INTAKE);
    // drive.goForward(2_tile);


}