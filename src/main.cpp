#include "main.h"
#include "config.h"
#include "pros/motors.h"
#include "pros/rtos.h"
#include "robodash/views/image.hpp"
#include "subsystems/classes.hpp"
#include "subsystems/systemconfig.hpp"
#include "api.h"
#include "filtersettings/interface.hpp"
#include "filtersettings/filterconfig.hpp"
#include "autos.h"
#include "autoselector/autoselector.hpp"
#include <iostream>

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

// rd::Selector selector({
// 	{"Red Ring Side SAWP", redringSideSigSWP},
// 	{"Red Goal Side SAWP", redgoalSideSigSWP},
// 	{"Blue Ring Side SAWP", blueringSideSigSWP},
// 	{"Blue Goal Side SAWP", bluegoalSideSigSWP},
// 	{"Red Right Rush", redRightRush},
// 	{"Blue Left Rush", blueLeftRush},
// 	{"Skills", skills},
// 	{"AntiJam Test", antiJamTest},
// 	{"Blue Ring Side Two", blueRingSideTwo},
// 	{"Blue Ring Side Elim", blueRingElims},
// 	{"Red Ring Side Elim", redRingElims},
// 	{"Red Ring Two", redRingTwo},
// 	{"Red Ring No Alliance", redRingNoAlliance},
// 	{"Red Goal Two", redGoalTwo},
// 	{"Move Off Line", moveOffLine},
// 	{"Blue Goal Two", blueGoalTwo}
// });

void testFilter() {
	while (1) {
	// int hue = intakeInstance.filterHue(redlow, redhigh, bluelow, bluehigh);
	// printf("Filter: %i ", hue);
		printf("IMU: %.5f", imu.get_heading());
		pros::delay(200);
	}
}

void updateLift() {
	while (1) {
		liftInstance.updateState();
		pros::delay(20);
	}
}
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void odomTest() {
	while (1) {
		printf("X: %f, Y: %f \n", chassis.getPose().x, chassis.getPose().y);
		// printf("X: %f", chassis.getPose().x);
		pros::delay(20);
	}
}


void initialize() {
    intakeInstance.startControlTask();
    intakeInstance.toggleSort(true);
    intakeInstance.setColor(red);
	rotLift.reset_position();
	pros::delay(300);
	chassis.calibrate(true);
	pros::Task liftController(updateLift, "liftController");
	pros::Task odomText(odomTest, "odomText");
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}


/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	// selector.run_auton();
	if (!imu.is_calibrating()) {
		// selector.run_auton();
		// skills();
		// redringSideSigSWP();
		// blueringSideSigSWP();
		// blueRingElims();
		// blueGoalElims();
		// redRingElims();
		// blueRingQuals();
		// redGoalQuals();
		// redGoalRush();
		redRingQuals();
		// redRingTwo();
		// blueRingElims();
		// blueLeftRush();
		// testOdomplease();
		// measure_offsets();
		// redGoalSAWP();
		// blueGoalRush();
		// redGoalTwo();
		// redGoalElimSafe();

	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void testColor() {
	while (true) {
		float hue = colorSensor.get_hue();
		float saturation = colorSensor.get_saturation();
		float brightness = colorSensor.get_brightness();
		printf("Hue: %.2f, Saturation: %.2f, Brightness: %.2f\n", hue, saturation, brightness);
		pros::delay(100);
	}
}





void opcontrol() {
	// pros::Task dadada(testColor, "dadada");
	while (true) {
		driveControl();
		mogoControl();
		intakeControl();
		liftControl();
		doinkControl();
		pros::delay(20);                               // Run for 20 ms then update
		// if (master.get_digital(DIGITAL_A) && master.get_digital(DIGITAL_RIGHT)) {
		// 	autonomous();
    	// }
	}
}
