#include "subsystems/classes.hpp"
#include "subsystems/systemconfig.hpp"
#include "api.h"
#include "config.h"
#include "main.h"
#include "pros/misc.h"

void driveControl() {
    chassis.tank(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y), true);
}

void intakeControl() {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        intakeInstance.move(127, 127);
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        intakeInstance.move(-127, -127);
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        intakeInstance.move(127, -30);
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        intakeInstance.move(-127, 0);
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        intakeInstance.move(127, -30);
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        intakeInstance.move(70, 127);
    }
    else {
        intakeInstance.stop();
    }
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        intakeInstance.toggleSort(!intakeInstance.getSortState());
    }
}

void mogoControl() {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
        mogoInstance.toggle();
    }
}

void doinkControl() {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        doinkerInstance.toggle();
    }
}

void liftControl() {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
        liftInstance.scroll();
    }
    else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        liftInstance.stow();
    }
    else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        liftInstance.wall();
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
        liftInstance.offsetPos();
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        liftInstance.offsetNeg();
    }
}
