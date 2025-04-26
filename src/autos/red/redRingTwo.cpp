#include "api.h"
#include "lemlib/api.hpp"
#include "filtersettings/filtertuning.hpp"
#include "config.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include "pros/rtos.hpp"
#include "subsystems/classes.hpp"


void redRingTwo() {
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
    //center ring
    intakeInstance.move(127, 127);
    chassis.turnToPoint(-8.8, 40, 700);
    chassis.moveToPoint(-8.8, 40, 900);
    //last ring
    chassis.moveToPoint(-16.7, 28.5, 900, {.forwards=false});
    chassis.turnToPoint(-23.2, 47, 700);
    chassis.moveToPoint(-23.2, 47, 900);
    //ladder touch
    chassis.moveToPoint(-23.0, 22.4, 900, {.forwards=false});
    chassis.turnToPoint(-23.0, 11.9, 700);
    chassis.moveToPoint(-23.0, 11.9, 900);
    liftInstance.scorewall();
}
