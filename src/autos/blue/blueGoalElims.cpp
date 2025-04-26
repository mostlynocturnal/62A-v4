#include "api.h"
#include "lemlib/api.hpp"
#include "filtersettings/filtertuning.hpp"
#include "config.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include "pros/rtos.hpp"
#include "subsystems/classes.hpp"
#include "autos.h"

void blueGoalRush() {
    chassis.setPose(50.1, -35.7, -95);
    intakeInstance.setColor(blue);
    intakeInstance.move(127, 0);
    liftInstance.scorewall();
    chassis.moveToPose(12.6, -40.7, -95, 2000, {.lead=.1, .minSpeed=60, .earlyExitRange=8.5});
    chassis.waitUntil(27);
    liftInstance.full();
    chassis.moveToPoint(40, -37, 900, {.forwards=false, .minSpeed=30, .earlyExitRange=3});
    chassis.waitUntilDone();
    liftInstance.stow();
    doinkerInstance.doink();
    chassis.moveToPoint(23.7, -49.2, 1000);
    chassis.turnToPoint(31, -20, 800, {.forwards=false});
    chassis.moveToPoint(31, -16, 1400, {.forwards=false});
    chassis.waitUntilDone();
    mogoInstance.clamp();
    doinkerInstance.undoink();
    pros::delay(20);
    intakeInstance.move(127, 127);
    chassis.moveToPoint(42.6, -39.5, 1000, {.minSpeed=50, .earlyExitRange=5});
    doinkerInstance.doink();
    chassis.moveToPoint(57.7, -55.7, 1000, {.maxSpeed=70, .minSpeed=30});
    chassis.waitUntilDone();
    chassis.tank(0, 127);
    pros::delay(300);
    chassis.turnToHeading(70, 600);
    chassis.waitUntil(50);
    doinkerInstance.undoink();
    chassis.waitUntilDone();
    chassis.moveToPose(70, -32, 0, 1000, {.lead=.3, .minSpeed=60, .earlyExitRange=7});

}
