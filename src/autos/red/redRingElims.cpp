#include "api.h"
#include "lemlib/api.hpp"
#include "filtersettings/filtertuning.hpp"
#include "config.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include "pros/rtos.hpp"
#include "subsystems/classes.hpp"
#include "autos.h"


void redRingElims() {
    intakeInstance.setColor(red);
    chassis.setPose(1, 0, 90);
    chassis.turnToHeading(140, 500);
    moveRelative(7, 127, 500);
    liftInstance.full();
    intakeInstance.stop();
    pros::delay(200);

    //mogo
    lemlib::Pose mogo = lemlib::Pose(-12, 33);
    chassis.moveToPoint(mogo.x, mogo.y, 1200, {.forwards=false, .minSpeed=20, .earlyExitRange=2});
    chassis.waitUntil(5);
    liftInstance.stow();
    chassis.waitUntilDone();
    mogoInstance.clamp();
    pros::delay(50);

    //center rings
    // lemlib::Pose ring1 = lemlib::Pose(-23, 45);
    intakeInstance.move(127, 127);
    chassis.moveToPose(-42, 43, -90, 2200, {.minSpeed=80, .earlyExitRange=40});

    // third ring
    chassis.moveToPoint(-17, 36.7, 1000, {.forwards=false, .minSpeed=40, .earlyExitRange=3});
    chassis.turnToPoint(-36.8, 26, 700, {.minSpeed=30, .earlyExitRange=3});
    chassis.moveToPoint(-36.8, 26, 700, {.minSpeed=40, .earlyExitRange=5});
    intakeInstance.move(127, 127);
    chassis.moveToPose(-17, 26, -135, 1000, {.forwards=false, .lead=.25, .minSpeed=40, .earlyExitRange=5});
    liftInstance.scorewall();

    // to corner
    chassis.moveToPoint(-47.7, -8.7, 2000, {.minSpeed=50, .earlyExitRange=6}); // real pose
    chassis.waitUntilDone();
    chassis.tank(127, 20);
    pros::delay(300);
    chassis.cancelMotion();
    chassis.moveToPoint(-10, 11, 1000, {.forwards=false, .minSpeed=40, .earlyExitRange=6});
    chassis.turnToPoint(3, 11, 700, {.minSpeed=40, .earlyExitRange=2});
    chassis.moveToPose(40, 13, 90, 2000, {.lead=.1, .maxSpeed=100, .minSpeed=20});
}
