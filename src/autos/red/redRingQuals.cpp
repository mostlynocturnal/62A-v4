#include "api.h"
#include "lemlib/api.hpp"
#include "filtersettings/filtertuning.hpp"
#include "config.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include "pros/rtos.hpp"
#include "subsystems/classes.hpp"
#include "autos.h"

void redRingQuals() {
    intakeInstance.setColor(red);
    chassis.setPose(1, 0, 90);
    chassis.turnToHeading(140, 500);
    moveRelative(7.75, 127, 500);
    liftInstance.full();
    intakeInstance.stop();
    pros::delay(200);

    //mogo
    lemlib::Pose mogo = lemlib::Pose(-12, 30);
    chassis.moveToPoint(mogo.x, mogo.y, 1200, {.forwards=false});
    chassis.waitUntil(5);
    liftInstance.stow();
    chassis.waitUntilDone();
    mogoInstance.clamp();
    pros::delay(50);

    //center rings
    // lemlib::Pose ring1 = lemlib::Pose(-23, 45);
    intakeInstance.move(127, 127);
    chassis.moveToPose(-42, 44, -90, 2200, {.minSpeed=70, .earlyExitRange=40});

    // third ring
    chassis.moveToPoint(-17, 36.7, 1000, {.forwards=false, .minSpeed=40, .earlyExitRange=3});
    chassis.turnToPoint(-36.8, 26, 700, {.minSpeed=30, .earlyExitRange=3});
    chassis.moveToPoint(-36.8, 26, 700, {.minSpeed=40, .earlyExitRange=5});
    intakeInstance.move(127, 127);
    chassis.moveToPose(-17, 26, -135, 1000, {.forwards=false, .lead=.25, .minSpeed=40, .earlyExitRange=5});

    chassis.moveToPose(-6, 13, 90, 2600, {.lead=.1, .minSpeed=10});
    chassis.moveToPoint(22, 13, 3000, {.maxSpeed=50});

    chassis.moveToPoint(-12, 30, 1000, {.forwards=false});
    liftInstance.scorewall();
    chassis.turnToHeading(45, 600);
    chassis.waitUntilDone();
    moveRelative(20, 127, 700);
}
