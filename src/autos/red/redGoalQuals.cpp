#include "api.h"
#include "lemlib/api.hpp"
#include "filtersettings/filtertuning.hpp"
#include "config.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include "pros/rtos.hpp"
#include "subsystems/classes.hpp"

void redGoalQuals() {
    intakeInstance.setColor(red);
    chassis.setPose(-58.6, -11.3, 0);
    //alliance
    chassis.moveToPoint(-60.7, -7.6, 500);
    chassis.turnToPoint(-70, -2, 600);
    intakeInstance.stop();
    liftInstance.full();
    pros::delay(200);
    //mogo
    chassis.moveToPoint(-17, -30, 1400, {.forwards=false});
    chassis.waitUntilDone();
    liftInstance.stow();
    mogoInstance.clamp();
    pros::delay(10);
    //second ring
    intakeInstance.move(127, 127);
    chassis.turnToPoint(-22.1, -47, 600);
    chassis.moveToPoint(-22.1, -50, 1000);

    //third
    chassis.moveToPose(-48.5, -9.7, 0, 1600, {.lead=.1, .minSpeed=40});
    chassis.moveToPoint(-48.5, 16, 1500, {.maxSpeed=30});

    // move to ladder touch
    chassis.moveToPoint(-29.1, -18.1, 900, {.forwards=false});
    chassis.turnToPoint(-11.9, -10, 700);
    liftInstance.scorewall();
    chassis.moveToPoint(-11.9, -10, 900);
}
