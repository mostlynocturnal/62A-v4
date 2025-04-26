#include "api.h"
#include "lemlib/api.hpp"
#include "filtersettings/filtertuning.hpp"
#include "config.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include "pros/rtos.hpp"
#include "subsystems/classes.hpp"

void redGoalTwo() {
    intakeInstance.setColor(blue);
    chassis.setPose(-58.6, -11.3, 0);
    //alliance
    liftInstance.ready();
    intakeInstance.move(0, 127);
    chassis.moveToPoint(-58.6, -8.3, 500);
    chassis.turnToPoint(-70, 0, 600);
    intakeInstance.stop();
    liftInstance.full();
    pros::delay(300);
    //mogo
    chassis.moveToPoint(-19, -26, 1400, {.forwards=false});
    liftInstance.stow();
    chassis.waitUntilDone();
    mogoInstance.clamp();
    pros::delay(20);
    //second ring
    intakeInstance.move(127, 127);
    chassis.turnToPoint(-22.1, -47, 600);
    chassis.moveToPoint(-22.1, -50, 1000);
    // move to ladder touch
    chassis.moveToPoint(-25.1, -24.1, 900, {.forwards=false});
    chassis.turnToPoint(-11.9, -24.1, 700);
    chassis.moveToPoint(-11.9, -24.1, 900);
    liftInstance.scorewall();
}
