#include "api.h"
#include "lemlib/api.hpp"
#include "filtersettings/filtertuning.hpp"
#include "config.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include "pros/rtos.hpp"
#include "subsystems/classes.hpp"

void redGoalSAWP() {
    intakeInstance.setColor(red);
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
    //next mogo transition
    chassis.turnToPoint(-46, -15, 800);
    chassis.moveToPoint(-46, -15, 1200);
    //drop mogo
    chassis.turnToPoint(-46, -6, 600);
    mogoInstance.release();
    intakeInstance.stopOnColor(red);
    chassis.moveToPoint(-46, 2, 1500, {.maxSpeed=60, .minSpeed=30, .earlyExitRange=3});
    chassis.moveToPoint(-46, 19, 900);
    //second mogo
    chassis.turnToPoint(-22, 22, 600, {.forwards=false});
    chassis.moveToPoint(-22, 22, 900, {.forwards=false});
    chassis.waitUntilDone();
    mogoInstance.clamp();
    pros::delay(20);
    // last ring
    intakeInstance.move(127, 127);
    chassis.turnToPoint(-26, 37, 600);
    chassis.moveToPoint(-26, 37, 600);
    chassis.moveToPoint(-26, 22, 800, {.forwards=false});
    chassis.turnToPoint(-35, -4, 700);
    chassis.moveToPoint(-35, -4, 900);
    liftInstance.scorewall();
}
