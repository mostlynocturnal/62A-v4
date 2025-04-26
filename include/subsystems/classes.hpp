#pragma once
#include "api.h"
#include "lemlib/pid.hpp"
#include "pros/adi.hpp"
#include <sys/_stdint.h>

enum Color {
    red = 0,
    blue = 1,
    none = 2
};

class Stopwatch {
        private:
            int start;
        public:
            Stopwatch();
            void reset();
            int elapsed();
};

class Intake {
    public:
        Intake(pros::Motor* intakeMotor, pros::Motor* pickupMotor, pros::Optical* opticalSensor, pros::adi::Pneumatics* intakeRaise, pros::adi::DigitalIn* limit, Color sort);
        void startControlTask();
        void move(float pickup, float hooks);
        void stop();
        Color getDetected();
        void setColor(Color c);
        Color getColor();
        void stopOnColor(Color col);
        void toggleSort(bool sortState);
        bool getSortState();
        void raise();
        void lower();
        bool intaking();
        bool intakeStopped();
        uint32_t intakeStartTime;
        uint32_t intakeStart();
        int intakeTime(uint32_t intakeStart);
    private:
        std::unordered_map<Color, std::pair<float, float>> colorHues{
            {red, {350, 15}}, {blue, {180, 270}}};
        std::unordered_map<Color, int> colorCounts{
            {red, 0}, {blue, 0}};
        std::unordered_map<Color, std::pair<int, int>> colorTimes{{red, {50, 470}}, {blue, {108, 135}}};
        float pickupvel;
        float hookvel;
        pros::Motor* intakeMotor;
        pros::Motor* pickupMotor;
        pros::Optical* opticalSensor;
        pros::adi::Pneumatics* intakeRaise;
        pros::adi::DigitalIn *limit;
        pros::Task *task = nullptr;
        Stopwatch sortTimer;
        Color colorToSort = none;
        double sortDist = 300;
        bool ringSeen = false;
        bool liftClear;
        bool taskBlocked;
        bool sortEnabled;
        Color colorDetected;
        Color colorToStop = none;

        Color detectColor();
        void control();

        void handleAutoStop(Color col);
        void handleColorSort(Color col, bool liftClear);
};

class Mogo {
    public:
        Mogo(pros::adi::Pneumatics* mogoPiston);
        void clamp();
        void release();
        void toggle();

    private:
        pros::adi::Pneumatics* mogoPiston;
};

class Lift {
    public:
        enum States {
            STOW,
            READY,
            WALL,
            WALLSCORE,
            FULLCIRCLE
        };
        Lift(pros::Motor* liftMotor, pros::Rotation* liftRot, lemlib::PID liftPID, float stowPos, float readyPos, float wallPos, float wallScore, float fullCircle, float gearRatio);
        void stow();
        void ready();
        void wall();
        void scorewall();
        void scroll();
        States getState();
        void setState(Lift::States state);
        void updateState();
        void setBrake(pros::motor_brake_mode_e brakeMode);
        void moveTime(float time, float power);
        bool getStopped();
        void full();
        void offsetPos();
        void offsetNeg();

    private:
        bool stopped;
        float setPosition;
        float currentPosition;
        float error;
        lemlib::PID liftPID;
        float stowPos;
        float readyPos;
        float wallPos;
        float wallScore;
        float fullCircle;
        pros::Motor* liftMotor;
        pros::Rotation* liftRot;
        float gearRatio;
        States state;
};

class Doinker {
    public:
        Doinker(pros::adi::Pneumatics* doinkerPiston);
        void doink();
        void undoink();
        void toggle();

    private:
        pros::adi::Pneumatics* doinkerPiston;
};
