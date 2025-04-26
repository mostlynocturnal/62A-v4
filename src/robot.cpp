#include "api.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/optical.hpp"
#include <cmath>

pros::MotorGroup left_motors({-1, -8, -11}, pros::MotorGearset::blue);
pros::MotorGroup right_motors({4, 9, 13}, pros::MotorGearset::blue);

pros::Motor intake(-3, pros::MotorGearset::blue);
pros::Motor pickup(10);

pros::Motor lift(21, pros::MotorGearset::green);

pros::Imu imu(14);
pros::Optical colorSensor(17);

pros::adi::Pneumatics mogo(7, false);
pros::adi::Pneumatics doinker(2, false);
pros::adi::Pneumatics intakeRaise(8, false);

pros::Rotation vertodom(-6);
pros::Rotation horzodom(-2);
pros::Distance sideDist(17);

pros::Optical color(1);
pros::Rotation rotLift(19);
pros::adi::DigitalIn limit(NAN);
