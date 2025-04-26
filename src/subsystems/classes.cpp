#include "subsystems/classes.hpp"
#include "config.h"
#include "liblvgl/core/lv_event.h"
#include "pros/motors.h"
#include <cmath>
#include <cstdlib>

Stopwatch::Stopwatch() {
    start = pros::millis();
}

void Stopwatch::reset() {
    start = pros::millis();
}

int Stopwatch::elapsed() {
    return pros::millis() - start;
}

Intake::Intake(pros::Motor* intakeMotor_, pros::Motor* pickupMotor_, pros::Optical* opticalSensor, pros::adi::Pneumatics* intakeRaise, pros::adi::DigitalIn* limit, Color sort)
    : intakeMotor(intakeMotor_), pickupMotor(pickupMotor_), opticalSensor(opticalSensor), intakeRaise(intakeRaise), limit(limit), colorToSort(sort) {
    opticalSensor -> set_integration_time(5);
    }

void Intake::startControlTask() {
    if (task == nullptr) {
        task = new pros::Task{[this] {
            while (true) {
                control();
                pros::delay(10);
            }
        }};
    }
}

void Intake::control() {
    Lift::States liftState = liftInstance.getState();
    bool liftClear = !(liftState == Lift::READY);
    Color col = detectColor();

    if (col != none) {
        ringSeen = true;
    }
    if (colorToStop != none) {
        handleAutoStop(col);
    }
    if (colorToSort != none && sortEnabled && hookvel > 0) { // && hookvel > 0
        handleColorSort(col, liftClear);
    }
    intakeMotor->move(hookvel);
    pickupMotor->move(pickupvel);
    if (hookvel != 0 || pickupvel != 0) opticalSensor->set_led_pwm(100);
    else {
        opticalSensor->set_led_pwm(0);
        colorCounts[blue] = 0;
        colorCounts[red] = 0;
    }
    if (hookvel <= 0) {
        sortTimer.reset();
        ringSeen = false;
    }
}

Color oppositeColor(Color c) {
    if (c == blue) return red;
    else if (c == red) return blue;
    return none;
}

Color Intake::getColor() {return colorToSort;}

void Intake::setColor(Color c) {this->colorToSort = c;}

void Intake::toggleSort(bool sortState) {this->sortEnabled=sortState;}

bool Intake::getSortState() {return this->sortEnabled;}

Color Intake::detectColor() {
    int check = 2;
    float hue = opticalSensor->get_hue();
    double dist = opticalSensor->get_proximity();
    int distRange = 100;
    int count = 2;
    if (dist > distRange) {
        if ((hue >= colorHues[red].first) || (hue <= colorHues[red].second)) {
            return red;
        }
        else if ((colorHues[blue].first <= hue) && (hue <= colorHues[blue].second)) {
            return blue;
        }
    }
    colorDetected = none;
    return none;
}

void Intake::stopOnColor(Color col) {
    this->colorToStop=col;
}

void Intake::move(float pickup, float hooks) {
    this -> pickupvel = pickup;
    this -> hookvel = hooks;
    this->intakeStartTime = pros::millis();
    colorToStop = none;
}

void Intake::stop() {
    hookvel = 0;
    pickupvel = 0;
}

void Intake::handleAutoStop(Color col) {
    if (col==colorToStop) {
        hookvel=0;
        colorToStop = none;
    }
}

void Intake::handleColorSort(Color col, bool liftClear) {
    if (col != none) {
        if (col == oppositeColor(colorToSort)) {taskBlocked = true;}
        else if (col == colorToSort) {taskBlocked = false;}
    }
    if (taskBlocked && liftClear) {
        master.rumble(".");
        sortTimer.reset();
        bool prev = 0;
        intakeMotor->tare_position();
        while (sortTimer.elapsed() < colorTimes[col].first && intakeMotor->get_position() < colorTimes[col].second) {
            printf("pos: yuhhh %f ", intakeMotor->get_position());
            intakeMotor->move(127);
            pros::delay(10);
        }
        intakeMotor->move(-80);
        pros::delay(150);
        taskBlocked=false;
        sortTimer.reset();
    }
}

int Intake::intakeTime(uint32_t intakeStart) {return (pros::millis() - intakeStart);}

uint32_t Intake::intakeStart() {return (this->intakeStartTime);}

void Intake::raise() {intakeRaise -> extend();}

void Intake::lower() {intakeRaise -> retract();}

bool Intake::intaking() {
    if (intakeMotor -> get_target_velocity() == 600) {return true;}
    return false;
}

bool Intake::intakeStopped() {
    if (intakeMotor -> get_actual_velocity() < 2.5 && intaking()) {return true;}
    return false;
}

Mogo::Mogo(pros::adi::Pneumatics* mogoPiston_)
    : mogoPiston(mogoPiston_) {}

void Mogo::clamp() {
    mogoPiston -> extend();
}

void Mogo::release() {
    mogoPiston -> retract();
}

void Mogo::toggle() {
    mogoPiston -> toggle();
}

Doinker::Doinker(pros::adi::Pneumatics* doinkerPiston_)
    : doinkerPiston(doinkerPiston_) {}

void Doinker::doink() {
    doinkerPiston -> extend();
}

void Doinker::undoink() {
    doinkerPiston -> retract();
}

void Doinker::toggle() {
    doinkerPiston -> toggle();
}


Lift::Lift(pros::Motor* liftMotor, pros::Rotation* liftRot, lemlib::PID liftPID, float stowPos, float readyPos, float wallPos, float wallScore, float fullCircle, float gearRatio)
    : liftMotor(liftMotor), liftRot(liftRot), liftPID(liftPID), stowPos(stowPos), readyPos(readyPos), wallPos(wallPos), wallScore(wallScore),fullCircle(fullCircle), gearRatio(gearRatio), state(STOW) {}

void Lift::stow() {
    state = STOW;
}

void Lift::ready() {
    if (state != READY) {
        state = READY;
    }
    else {
        state = STOW;
    }
}

void Lift::wall() {
    if (state != WALL) {
        state = WALL;
    }
    else {
        state = WALLSCORE;
    }
}

void Lift::scorewall() {
    state = WALLSCORE;
}

void Lift::scroll() {
    if (state == STOW) {
        state = READY;
    }
    else if (state == READY || state == WALL || state == WALLSCORE) {
        state = FULLCIRCLE;
    }
    else if (state == WALLSCORE || state == FULLCIRCLE) {
        state = STOW;
    }
}

void Lift::full() {
    state = FULLCIRCLE;
}

Lift::States Lift::getState() {
    return(this->state);
}

void Lift::updateState() {
    switch (state) {
        case STOW:
            this->setPosition = stowPos;
            break;
        case READY:
            this->setPosition = readyPos;
            break;
        case WALL:
            this->setPosition = wallPos;
            break;
        case WALLSCORE:
            this->setPosition = wallScore;
            break;
        case FULLCIRCLE:
            this->setPosition = fullCircle;
    };
    this->currentPosition = (liftMotor -> get_position() * gearRatio);
    this->error = setPosition - currentPosition;
    liftMotor -> move(liftPID.update(error));
}
void Lift::offsetPos() {
    switch (state) {
        case STOW:
            stowPos += 5;
            break;
        case READY:
            readyPos += 5;
            break;
        case WALL:
            wallPos += 5;
            break;
        case WALLSCORE:
            wallScore += 5;
            break;
        case FULLCIRCLE:
            fullCircle += 5;
            break;
    }
}

void Lift::offsetNeg() {
    switch (state) {
        case STOW:
            stowPos -= 5;
            break;
        case READY:
            readyPos -= 5;
            break;
        case WALL:
            wallPos -= 5;
            break;
        case WALLSCORE:
            wallScore -= 5;
            break;
        case FULLCIRCLE:
            fullCircle -= 5;
            break;
    }
}
