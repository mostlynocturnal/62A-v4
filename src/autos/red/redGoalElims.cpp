#include "api.h"
#include "lemlib/api.hpp"
#include "filtersettings/filtertuning.hpp"
#include "config.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include "pros/rtos.hpp"
#include "subsystems/classes.hpp"
#include "autos.h"

void redGoalRush() {
    chassis.setPose(-50.1, -35.7, 90);
    intakeInstance.setColor(red);
    liftInstance.scorewall();
    chassis.moveToPose(-14.5, -35.5, 150, 1400, {.lead=.01, .minSpeed=85, .earlyExitRange=3});
    chassis.waitUntil(44);
    liftInstance.full();
    chassis.moveToPoint(-35, -23, 1500, {.forwards=false});
    chassis.waitUntil(12);
    liftInstance.stow();
    chassis.waitUntilDone();
    mogoInstance.clamp();
    chassis.moveToPoint(-23.7, -53, 1000);
    intakeInstance.move(127, 127);
    chassis.moveToPose(-50, -35, -130, 1000, {.lead=.1, .minSpeed=40, .earlyExitRange=10});
    chassis.moveToPoint(-64.4, -75, 1200);
    doinkerInstance.doink();
    chassis.turnToPoint(-50, -64.6, 800);
    chassis.waitUntil(20);
    doinkerInstance.undoink();
    chassis.moveToPose(-33.0, -67, 90, 2000, {.minSpeed=50, .earlyExitRange=5});
    // doinkerInstance.undoink();
    // pros::delay(20);
    // intakeInstance.move(127, 127);
    // chassis.moveToPoint(-42.6, -39.5, 1000, {.minSpeed=50, .earlyExitRange=5});
    // doinkerInstance.doink();
    // chassis.moveToPoint(-57.7, -55.7, 1000, {.maxSpeed=70, .minSpeed=30});
    // chassis.waitUntilDone();
    // chassis.tank(0, 127);
    // pros::delay(300);
    // chassis.turnToHeading(-70, 600);
    // chassis.waitUntil(50);
    // doinkerInstance.undoink();
    // chassis.waitUntilDone();
    // chassis.moveToPose(-70, -32, 0, 1000, {.lead=.3, .minSpeed=60, .earlyExitRange=7});

}
