// mechanumDriveTrain.h
#ifndef MECHANUM_DRIVETRAIN_H
#define MECHANUM_DRIVETRAIN_H

#include "Motor.h"
#include "MotorControllers.h"
#include <cmath>

class MechanumDriveTrain {
private:
    MotorControllers& controller;
    uint8_t frontLeft;
    uint8_t frontRight;
    uint8_t backLeft;
    uint8_t backRight;
    bool isFieldCentric;

public:
    // Constructor
    MechanumDriveTrain(MotorControllers& controller, uint8_t FrontL, uint8_t FrontR, uint8_t BackL, uint8_t BackR);

    // Drive method
    void drive(int x, int y, int turn);

    void setBrake();

    void setCoast();
};

#endif // MECHANUM_DRIVETRAIN_H