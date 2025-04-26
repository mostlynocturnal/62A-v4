#pragma once
#include "api.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/misc.h"
#include "subsystems/classes.hpp"

inline pros::Controller master(pros::E_CONTROLLER_MASTER);
extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;
extern pros::Motor intake;
extern pros::Motor pickup;
extern pros::Motor lift;
extern pros::adi::Pneumatics mogo;
extern pros::adi::Pneumatics doinker;
extern pros::adi::Pneumatics intakeRaise;
extern pros::Rotation vertodom;
extern pros::Rotation horzodom;
extern pros::Distance sideDist;
extern pros::Optical colorSensor;
extern pros::Rotation rotLift;
extern pros::adi::DigitalIn limit;

extern pros::Imu imu;

inline lemlib::PID liftPID(1, 0, 5);

inline Lift liftInstance(&lift, &rotLift, liftPID, 4, 63, 215, 420, 650, (1.0/4.0));

inline float redlow = 0;
inline float redhigh = 20;

inline float bluelow = 200;
inline float bluehigh = 225;

inline double trackWidth = 13;
inline int WheelSize = lemlib::Omniwheel::NEW_325;
inline int rpm = 450;
inline int HorzDrift = 8;

inline lemlib::Drivetrain drivetrain(&left_motors, &right_motors, trackWidth, WheelSize, rpm, HorzDrift);

inline lemlib::TrackingWheel vert(&vertodom, 2, 1.960015);
inline lemlib::TrackingWheel horz(&horzodom, 2, 0.589833);


inline lemlib::OdomSensors odom(&vert,
                                nullptr,
                                &horz,
                                nullptr,
                                &imu);

// inline lemlib::OdomSensors odom(nullptr,
//                                 nullptr,
//                                 nullptr,
//                                 nullptr,
//                                 &imu);

inline Intake intakeInstance(&intake, &pickup, &colorSensor, &intakeRaise, &limit, Color::red);

inline Mogo mogoInstance(&mogo);

inline Doinker doinkerInstance(&doinker);

inline lemlib::ControllerSettings lateral_controller(4.4, .025, 22, 5, 2, 200, 5, 500, 12);

inline lemlib::ExpoDriveCurve throttle(5, 5, 1.03);

inline lemlib::ControllerSettings angular_controller(3,
                                                    .025,
                                                    22,
                                                    3.25,
                                                    3,
                                                    200,
                                                    7,
                                                    500,
                                                    20);

// inline lemlib::ControllerSettings angular_controller(0,
//                                                     0,
//                                                     0,
//                                                     0,
//                                                     0,
//                                                     0,
//                                                     0,
//                                                     0,
//                                                     0);

inline lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, odom, &throttle);
