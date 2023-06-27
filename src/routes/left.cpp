#include "parameters.h"
#include "pros/screen.h"
#include "routes.h"
#include "drive.h"
#include "effectors.h"
#include "Console.h"

void Routes::left() {
    effectors.disablePiston();

    odometery.setPos({14_in, 108_in, 180_deg});
    
    while (true) {
        effectors.stepCataReset();
        pros::delay(10);
        if (effectors.shouldReset == false) break;
    }
    
    // spin roller    
    drive.goForward(4_in, {{0, 1}}, {{0.5, [](){
        effectors.outtake();
    } }} );
    effectors.delay(50_ms);
    effectors.stopIntake();


    drive.goBackward(6_in);

    
    // go to middle point
    drive.turnLeft(130_deg, {{0, 0.75}});
    
    drive.setToleranceParams(std::nullopt, std::nullopt, 3_s);

    drive.goForward(2.6_tile, {{0, 1}});
    
    drive.resetToleranceParams();
    
    // // turn to goal and shoot
    drive.turnRight(85_deg);
    effectors.enablePiston();
    drive.goBackward(3_in, {}, {{0.5, [](){
        effectors.shoot();
    }}});

    effectors.delay(100_ms);
    effectors.disablePiston();

    drive.goForward(7_in);
    drive.turnLeft(83_deg, {{0, 0.75}});
    drive.setToleranceParams(std::nullopt, std::nullopt, 3_s);
    drive.goForward(2.55_tile, {{0, 1}});
    drive.resetToleranceParams();

    drive.turnRight(40_deg);
    

    drive.setToleranceParams(std::nullopt, std::nullopt, 1.5_s);
    drive.goForward(7_in, {{0, 0.75}} );
    drive.resetToleranceParams();

    effectors.outtake();
    effectors.delay(350_ms);
    effectors.stopIntake();

    while (true) {
        effectors.stepCataReset();
        pros::delay(10);
        if (effectors.shouldReset == false) break;
    }

    // // go to other roller
    // drive.faceToPoint({108_in, 12_in}, false);
    // drive.goToPoint({108_in, 12_in}, false);

    // drive.faceToPoint({108_in, 108_in}, false);
    // drive.goBackward(2_in);
    // effectors.intake();
    // effectors.delay(100_ms);
    // effectors.stopIntake();
}