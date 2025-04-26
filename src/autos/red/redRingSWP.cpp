#include "api.h"
#include "lemlib/api.hpp"
#include "filtersettings/filtertuning.hpp"
#include "config.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include "pros/rtos.hpp"
#include "subsystems/classes.hpp"


void redRingSAWP() {
    intakeInstance.setColor(blue);
    chassis.setPose(-58.6, 11.3, 180);
    //alliance
    liftInstance.ready();
    intakeInstance.move(0, 127);
    chassis.moveToPoint(-58.6, 8.3, 500);
    chassis.turnToPoint(-70, 0, 600);
    intakeInstance.stop();
    liftInstance.full();
    pros::delay(300);
    //mogo
    chassis.moveToPoint(-22, 26, 1400, {.forwards=false});
    liftInstance.stow();
    chassis.waitUntilDone();
    mogoInstance.clamp();
    pros::delay(20);
    //center rings
    intakeInstance.move(127, 127);
    chassis.moveToPose(-9.4, 57, 0, 2500, {.minSpeed=60, .earlyExitRange=15});
    chassis.moveToPoint(-15.1, 32.1, 1000, {.forwards=false});
    chassis.turnToPoint(-24.1, 47, 600);
    chassis.moveToPoint(-25.1, 50, 1000);
    //next mogo transition
    chassis.turnToPoint(-46, 15, 800);
    chassis.moveToPoint(-46, 15, 1200);
    //drop mogo
    chassis.turnToPoint(-46, 6, 600);
    mogoInstance.release();
    chassis.moveToPoint(-46, 4, 1500, {.maxSpeed=60, .minSpeed=30, .earlyExitRange=3});
    chassis.moveToPoint(-46, -16, 900);
    chassis.waitUntil(17);
    intakeInstance.stop();
    //second mogo
    chassis.turnToPoint(-26, -22, 600, {.forwards=false});
    chassis.moveToPoint(-26, -22, 900, {.forwards=false});
    chassis.waitUntilDone();
    mogoInstance.clamp();
    pros::delay(20);
    // last ring
    intakeInstance.move(127, 127);
    chassis.turnToPoint(-26, -35, 600);
    chassis.moveToPoint(-26, -35, 600);
}
