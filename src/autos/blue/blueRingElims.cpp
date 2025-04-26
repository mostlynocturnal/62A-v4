#include "api.h"
#include "lemlib/api.hpp"
#include "filtersettings/filtertuning.hpp"
#include "config.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include "pros/rtos.hpp"
#include "subsystems/classes.hpp"

void blueRingElims() {
    intakeInstance.setColor(blue);
    chassis.setPose(-1, 0, -90);
    liftInstance.ready();
    intakeInstance.move(0, 127);
    chassis.moveToPoint(-4, 0, 700);
    chassis.turnToHeading(-135, 500);
    liftInstance.full();
    intakeInstance.stop();
    pros::delay(200);

    //mogo
    lemlib::Pose mogo = lemlib::Pose(12, 39);
    chassis.moveToPoint(mogo.x, mogo.y, 1200, {.forwards=false, .minSpeed=50, .earlyExitRange=3});
    chassis.waitUntil(5);
    liftInstance.stow();
    chassis.waitUntilDone();
    mogoInstance.clamp();
    pros::delay(50);

    //center rings
    intakeInstance.move(127, 127);
    chassis.moveToPose(39, 49, 90, 2200, {.minSpeed=60, .earlyExitRange=16});

    // third ring
    chassis.moveToPoint(17, 36.7, 1000, {.forwards=false, .earlyExitRange=3});
    intakeInstance.move(-127, 127);
    chassis.turnToPoint(36.8, 26, 700, {.earlyExitRange=3});
    chassis.moveToPoint(36.8, 26, 700, {.earlyExitRange=5});
    intakeInstance.move(127, 127);
    chassis.moveToPose(17, 26, 135, 1000, {.forwards=false, .lead=.25, .minSpeed=40, .earlyExitRange=5});
    // liftInstance.full(); not for testing

    // to corner
    chassis.moveToPoint(47.7, -8.7, 2000);
    chassis.moveToPoint(10, 7, 1000, {.forwards=false, .minSpeed=40, .earlyExitRange=6});
    chassis.turnToPoint(-3, 9, 700, {.minSpeed=40, .earlyExitRange=4});
    chassis.moveToPose(-6, 9, -90, 2000);
}
