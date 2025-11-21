// MotorControllers.h
#ifndef MOTOR_CONTROLLERS_H
#define MOTOR_CONTROLLERS_H

#include "driver/mcpwm.h"
#include <vector>
#include "Motor.h"

#define MOTOR_1_PIN_1 47
#define MOTOR_1_PIN_2 48
#define MOTOR_2_PIN_1 38
#define MOTOR_2_PIN_2 21
#define MOTOR_3_PIN_1 1
#define MOTOR_3_PIN_2 2
#define MOTOR_4_PIN_1 4
#define MOTOR_4_PIN_2 5
#define MOTOR_5_PIN_1 7
#define MOTOR_5_PIN_2 6
#define MOTOR_6_PIN_1 16
#define MOTOR_6_PIN_2 15

// Constants for motor IDs
#define MOTOR_1_ID 1
#define MOTOR_2_ID 2
#define MOTOR_3_ID 3
#define MOTOR_4_ID 4
#define MOTOR_5_ID 5
#define MOTOR_6_ID 6

class MotorControllers {
public:
    MotorControllers();
    void shutDown();
    void setAll(float percentage);
    void stopAll();
    void set(int motor, float percentage);
    void reverseAll();
    void reverse(int motor);
    void setCoast();
    void setBrake();
    Motor* getMotorById(int id);

private:
    std::vector<Motor> motors;
    int16_t percentToCycle(float percentage);
};

#endif