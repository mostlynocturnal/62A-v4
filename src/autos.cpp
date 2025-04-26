#include "api.h"
#include "lemlib/api.hpp"
#include "filtersettings/filtertuning.hpp"
#include "config.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/util.hpp"
#include "pros/rtos.hpp"
#include "subsystems/classes.hpp"

void testing() {
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(0, 20, 100000);
    printf("heading: %f", imu.get_heading());
}

void moveRelative(float distance, float maxSpeed, int timeout, float minspeed=0, float exit=0) {
    double headingRadians = chassis.getPose(true).theta;
    double startingX = chassis.getPose().x;
    double startingY = chassis.getPose().y;
    double deltaX = distance * sin(headingRadians);
    double deltaY = distance * cos(headingRadians);
    double newX = startingX + deltaX;
    double newY = startingY + deltaY;
    if (distance > 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=true, .maxSpeed=maxSpeed, .minSpeed=minspeed, .earlyExitRange=exit});
    }
    else if (distance < 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=false, .maxSpeed=maxSpeed, .minSpeed=minspeed, .earlyExitRange=exit});
    }
};
//make6000
void antiJam() {
    while(1) {
		if (intakeInstance.intaking() && !intakeRaise.is_extended()) {
			if ((intakeInstance.intakeTime(intakeInstance.intakeStart()) > 1400) && intakeInstance.intakeStopped()) {
				intake.move(-127);
				pros::delay(500);
				intakeInstance.move(127, 127);
			}
		}
		pros::delay(20);
    }
}

void tuning() {
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(0, 48, 10000);
    chassis.moveToPoint(0, 12, 10000);
}

void antiJamTest() {
    pros::Task antiJamControl(antiJam, "antiJamControl");
    intakeInstance.move(127, 127);
}

void jiggle() {
    intakeInstance.stop();
    pros::delay(75);
    intakeInstance.move(127, 127);
    pros::delay(20);
}

enum distSensorSide {
    POSITIVE_X,
    NEGATIVE_X,
    POSITIVE_Y,
    NEGATIVE_Y,
};

// void resetRobotPos(distSensorSide side) {

// }

// void remainDistFromWall(float drive, int dist, float maxspeed=127, int timeout=5000) {
//     double headingRadians = chassis.getPose(true).theta;
//     double startingX = chassis.getPose().x;
//     double startingY = chassis.getPose().y;
//     double deltaX = drive * sin(headingRadians);
//     double deltaY = drive * cos(headingRadians);
//     double newX = startingX + deltaX;
//     double newY = startingY + deltaY;
//     if (drive > 0) {
//         chassis.moveToPoint(newX, newY, timeout, {.forwards=true, .maxSpeed=maxspeed});
//     }
//     else if (drive < 0) {
//         chassis.moveToPoint(newX, newY, timeout, {.forwards=false, .maxSpeed=maxspeed});
//     }
//     while (chassis.isInMotion()) {
//         headingRadians = chassis.getPose(true).theta;
//         deltaX = drive * sin(headingRadians);
//         deltaY = drive * cos(headingRadians);
//         newX = startingX + deltaX;
//         newY = startingY + deltaY;
//         int currDist = sideDist.get_distance();
//         int wallError = dist - currDist;
//         if (lemlib::sgn(wallError) == 1) {
//             chassis.moveToPoint(newX, newY-3, timeout, {.forwards=false, .maxSpeed=maxspeed});
//             chassis.cancelMotion();
//         }
//         else {
//             chassis.moveToPoint(newX, newY+3, timeout, {.forwards=false, .maxSpeed=maxspeed});
//             chassis.cancelMotion();
//         }
//     }
// }

void redLeftWall() {
    chassis.setPose(0, 0, 0);
    liftInstance.wall();
    chassis.moveToPoint(0, 31.5, 1000, {.minSpeed=60, .earlyExitRange=5});
    chassis.moveToPoint(-6, 38, 700);
    chassis.waitUntil(5);
    intakeInstance.move(127, 0);
    chassis.moveToPoint(14, 27, 1000, {.forwards=false});
    chassis.waitUntilDone();
    moveRelative(-8, 70, 600);
    chassis.waitUntilDone();
    mogoInstance.clamp();
    pros::delay(400);
    intakeInstance.move(127, 127);
    chassis.turnToHeading(-90, 600);
    chassis.moveToPoint(-8, 25, 1600);
    chassis.turnToPoint(-25.5, 42, 800);
    chassis.moveToPoint(-25.5, 42, 1500);
    chassis.waitUntilDone();
    liftInstance.scorewall();
    pros::delay(800);
    moveRelative(-12.5, 80, 800);
    chassis.waitUntilDone();
    pros::delay(300);
    moveRelative(-30, 80, 1200);
    chassis.waitUntilDone();
    intakeInstance.stop();
}

// void skills() {
//     pros::Task antiJamControl(antiJam, "antiJamControl");
//     chassis.setPose(0, 0, 180);
//     liftInstance.full();
//     pros::delay(500);
//     moveRelative(-7, 80, 800);
//     chassis.waitUntilDone();
//     chassis.turnToPoint(-22, 6.5, 1000, {.forwards=false});
//     chassis.waitUntilDone();
//     moveRelative(-22, 80, 800);
//     chassis.waitUntilDone();
//     mogoInstance.clamp();
//     liftInstance.stow();
//     pros::delay(200);
//     chassis.turnToHeading(0, 600, {.minSpeed=30, .earlyExitRange=2});
//     chassis.waitUntil(4);
//     intakeInstance.move(127, 127);
//     chassis.waitUntilDone();
//     moveRelative(23, 70, 1000, 30, 2);
//     chassis.waitUntilDone();
//     antiJamControl.suspend();
//     chassis.turnToPoint(-45, 54, 1000);
//     chassis.waitUntilDone();
//     moveRelative(31.15, 80, 1000);
//     chassis.waitUntilDone();
//     liftInstance.ready();
//     chassis.turnToHeading(-90, 600);
//     chassis.waitUntilDone();
//     moveRelative(15, 65, 700);
//     chassis.waitUntilDone();
//     pros::delay(500);
//     jiggle();
//     pros::delay(50);
//     liftInstance.wall();
//     pros::delay(50);
//     pros::delay(50);
//     moveRelative(5, 80, 600);
//     chassis.waitUntil(2);
//     liftInstance.scorewall();
//     chassis.cancelMotion();
//     pros::delay(200);
//     moveRelative(8, 80, 300);
//     chassis.waitUntilDone();
//     moveRelative(-15, 70, 800);
//     chassis.waitUntilDone();
//     antiJamControl.resume();
//     liftInstance.stow();
//     intakeInstance.move(127, 127);
//     chassis.turnToHeading(180, 700, {.minSpeed=30, .earlyExitRange=2});
//     chassis.waitUntilDone();
//     moveRelative(25, 70, 1500, 30, 5);
//     chassis.waitUntilDone();
//     moveRelative(32, 50, 1500, 30, 2);
//     chassis.waitUntilDone();
//     chassis.turnToPoint(-60, 9, 600);
//     chassis.waitUntilDone();
//     moveRelative(20, 70, 800);
//     chassis.waitUntilDone();
//     moveRelative(-15, 60, 600);
//     chassis.waitUntilDone();
//     chassis.turnToHeading(45, 600);
//     chassis.waitUntilDone();
//     mogoInstance.release();
//     pros::delay(200);
//     moveRelative(-10, 127, 2000, 100);
//     chassis.waitUntilDone();

//     chassis.setPose(0, 0, chassis.getPose().theta);
//     pros::delay(200);
//     chassis.turnToHeading(49, 500);
//     chassis.waitUntilDone();
//     moveRelative(20, 80, 800, 30, 3);
//     chassis.waitUntilDone();
//     chassis.turnToHeading(90, 600);
//     chassis.waitUntilDone();
//     chassis.moveToPoint(52, 15, 4000);
//     chassis.waitUntilDone();
//     chassis.turnToHeading(0, 800);
//     chassis.waitUntilDone();
//     moveRelative(-30, 50, 1000);
//     chassis.waitUntilDone();
//     chassis.setPose(0, 0, 0);
//     pros::delay(50);
//     moveRelative(15.5, 90, 1000);
//     chassis.waitUntilDone();
//     chassis.turnToHeading(-90, 700);
//     chassis.waitUntilDone();
//     moveRelative(-28 , 70, 800);
//     chassis.waitUntilDone();
//     mogoInstance.clamp();
//     pros::delay(100);
//     chassis.waitUntilDone();
//     chassis.turnToHeading(0, 600);
//     chassis.waitUntilDone();
//     liftInstance.ready();
//     antiJamControl.suspend();
//     moveRelative(20, 70, 800);
//     chassis.waitUntilDone();
//     chassis.turnToHeading(34, 600);
//     chassis.waitUntilDone();
//     moveRelative(32, 70, 1000);
//     chassis.waitUntilDone();
//     liftInstance.wall();
//     chassis.turnToHeading(90, 600);
//     chassis.waitUntilDone();
//     intakeInstance.move(127, 127);
//     moveRelative(22, 80, 700);
//     chassis.waitUntilDone();
//     pros::delay(100);
//     liftInstance.scorewall();
//     moveRelative(2, 127, 200);
//     chassis.waitUntilDone();
//     antiJamControl.resume();
//     pros::delay(400);
//     moveRelative(-14.5, 70, 800);
//     chassis.waitUntilDone();
//     liftInstance.stow();
//     intakeInstance.move(127, 127);
//     chassis.turnToHeading(172.5, 700);
//     chassis.waitUntilDone();
//     moveRelative(25, 70, 1500);
//     chassis.waitUntilDone();
//     moveRelative(32, 50, 1500);
//     chassis.waitUntilDone();
//     chassis.turnToHeading(45, 600);
//     chassis.waitUntilDone();
//     moveRelative(20, 70, 800);
//     chassis.waitUntilDone();
//     moveRelative(-15, 60, 600);
//     chassis.waitUntilDone();
//     chassis.turnToHeading(-45, 600);
//     chassis.waitUntilDone();
//     mogoInstance.release();
//     pros::delay(200);
//     moveRelative(-20, 127, 1000, 90);
//     chassis.waitUntilDone();

//     chassis.setPose(0, 0, chassis.getPose().theta);
//     pros::delay(55);
//     chassis.turnToHeading(-35, 800);
//     chassis.waitUntilDone();
//     moveRelative(40, 127, 2000, 60);
//     chassis.waitUntilDone();
//     chassis.turnToHeading(-90, 600);
//     chassis.waitUntilDone();
//     intakeInstance.stop();
//     moveRelative(-38, 90, 1500);
//     chassis.waitUntilDone();
//     chassis.setPose(0, 0, -90);
//     pros::delay(10);
//     moveRelative(12, 127, 800);
//     chassis.waitUntilDone();
//     chassis.turnToHeading(-10, 600);
//     chassis.waitUntilDone();
//     intakeInstance.move(127, 0);
//     moveRelative(60, 80, 3000);
//     chassis.waitUntilDone();
//     chassis.turnToHeading(97.5, 600);
//     chassis.waitUntilDone();
//     moveRelative(-45, 127, 5000);
//     chassis.waitUntilDone();
//     mogoInstance.clamp();
//     chassis.setPose(0, 0, chassis.getPose().theta);
//     intakeInstance.move(127, 127);
//     pros::delay(50);
//     chassis.moveToPose(65, -30, 30, 3000, {.lead=.2});
//     chassis.waitUntilDone();
//     doinkerInstance.doink();
//     chassis.moveToPoint(70, 18, 1000);
//     chassis.waitUntilDone();
//     chassis.turnToHeading(-90, 700);
//     chassis.waitUntilDone();
//     doinkerInstance.undoink();
//     intakeInstance.stop();
//     chassis.turnToHeading(-135, 700);
//     chassis.waitUntilDone();
//     mogoInstance.release();
//     moveRelative(-20, 127, 1000);
//     chassis.waitUntilDone();
//     pros::delay(50);
//     chassis.resetLocalPosition();

//     moveRelative(30, 80, 1000);
//     chassis.waitUntil(10);
//     intakeInstance.stop();
//     chassis.waitUntilDone();
//     chassis.turnToHeading(-72, 700);
//     chassis.waitUntilDone();
//     moveRelative(100, 127, 5000, 80);

//     chassis.waitUntilDone();
//     chassis.turnToHeading(-35, 600);
//     chassis.waitUntilDone();
//     moveRelative(-60, 90, 1500);
//     chassis.waitUntil(20);
//     liftInstance.wall();
//     chassis.waitUntilDone();
//     intakeInstance.stop();
//     chassis.tank(-127, 0);
//     pros::delay(500);
//     chassis.tank(0, -127);
//     pros::delay(500);
//     chassis.tank(80, 80);

// }

void redRightRush() {
    chassis.setPose(0, 0, 0);
    intakeInstance.move(0, 127);
    moveRelative(29.5, 127, 1500, 100);
    chassis.waitUntil(9.75);
    liftInstance.full();
    chassis.waitUntilDone();
    pros::delay(300);
    moveRelative(-12.5, 127, 1000, 70);
    chassis.waitUntilDone();
    chassis.turnToHeading(50, 700);
    chassis.waitUntil(2);
    liftInstance.stow();
    chassis.waitUntilDone();
    moveRelative(15, 90, 800);
    chassis.waitUntilDone();
    chassis.turnToHeading(72, 600);
    chassis.waitUntilDone();
    moveRelative(-28, 90, 1000);
    chassis.waitUntilDone();
    mogoInstance.clamp();
    pros::delay(300);
    intakeInstance.move(127, 127);
    chassis.turnToHeading(152, 600);
    chassis.waitUntilDone();
    moveRelative(32, 80, 800);
    chassis.waitUntilDone();
    chassis.turnToHeading(82.5, 700);
    chassis.waitUntilDone();
    intakeInstance.stop();
    moveRelative(53, 100, 2000);
    chassis.waitUntil(10);
    doinkerInstance.doink();
    chassis.waitUntilDone();
    chassis.turnToHeading(20, 700);
    chassis.waitUntilDone();
    doinkerInstance.undoink();
    intakeInstance.move(127, 127);
    moveRelative(15, 80, 600);
    chassis.waitUntilDone();
    chassis.turnToHeading(-25, 600);
    chassis.waitUntilDone();
    pros::delay(600);
    mogoInstance.release();
    intakeInstance.stop();
    pros::delay(200);
    moveRelative(30, 80, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(-190, 700, {.direction=lemlib::AngularDirection::CW_CLOCKWISE});
    chassis.waitUntilDone();
}

void blueLeftRush() {
    chassis.setPose(0, 0, 0);
    intakeInstance.move(127, 0);
    moveRelative(29.5, 127, 1300, 100);
    chassis.waitUntil(10.25);
    liftInstance.full();
    chassis.waitUntilDone();
    pros::delay(300);
    moveRelative(-12, 127, 500, 70);
    chassis.waitUntil(5);
    liftInstance.stow();
    chassis.waitUntilDone();
    chassis.turnToHeading(-50, 700);
    chassis.waitUntilDone();
    moveRelative(15, 90, 800);
    chassis.waitUntilDone();
    chassis.turnToHeading(-72, 600);
    chassis.waitUntilDone();
    moveRelative(-32, 90, 1000);
    chassis.waitUntilDone();
    mogoInstance.clamp();
    pros::delay(300);
    intakeInstance.move(127,127);
    chassis.turnToHeading(-100, 800);
    chassis.waitUntilDone();
    moveRelative(43, 100, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(-140, 800);
    chassis.waitUntilDone();
    intakeInstance.stop();
    doinkerInstance.doink();
    moveRelative(50, 120, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(-190, 800);
    chassis.waitUntilDone();
    doinkerInstance.undoink();
    pros::delay(50);
    intakeInstance.move(127,127);
    moveRelative(15, 80, 800);
}

void redGoalElimSafe() {
    chassis.setPose(-51.3, -21.3, -90);
    moveRelative(-28, 127, 1000);
    chassis.waitUntilDone();
    mogoInstance.clamp();
    pros::delay(20);
    chassis.turnToPoint(-10.4, -6.4, 600);
    chassis.moveToPoint(-10.4, -6.4, 1400);
    chassis.waitUntilDone();
    doinkerInstance.doink();
    pros::delay(50);
    chassis.moveToPoint(-43.1, -41.4, 1300, {.forwards=false});
    chassis.waitUntilDone();
    doinkerInstance.undoink();
    intakeInstance.move(127, 127);
    chassis.moveToPose(-23, -41.5, 180, 2000, {.lead=.7});
    chassis.moveToPoint(-23, -52.2, 900);
    chassis.turnToPoint(-56.6, -61.0, 600);
    chassis.moveToPoint(-56.6, -61.0, 1200);
    chassis.waitUntil(15);
    intakeInstance.stop();
    doinkerInstance.doink();
    chassis.waitUntilDone();
    chassis.turnToPoint(-49.2, -51.7, 900, {.direction=lemlib::AngularDirection::CCW_COUNTERCLOCKWISE});
    doinkerInstance.undoink();
    chassis.moveToPoint(-32.0, -47.9, 900);
    chassis.waitUntilDone();
    mogoInstance.release();
    chassis.turnToPoint(-11.4, -47.9, 700, {.forwards=false});
    chassis.moveToPose(-11.4, -47.9, -90, 900, {.forwards=false, .lead=.1});
}

void testOdomplease() {
    chassis.setPose(0, 0, 0);
    moveRelative(72, 127, 100000);
}
