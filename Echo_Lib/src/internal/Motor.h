// Motor.h
#ifndef MOTOR_H
#define MOTOR_H

#include "driver/mcpwm.h"

class Motor {
public:
    Motor(mcpwm_unit_t unit, mcpwm_timer_t timer, int id, int pin1, int pin2);

    void setSpeed(int dutyCycle);
    void reverseDirection();
    void disablePWM();
    void setCoastMode();
    void setBrakeMode();
    int getId() const;
    bool isReversed() const;

private:
    int id;                 // Motor ID
    int pin1, pin2;         // GPIO pins
    bool reversed;          // Direction flag
    mcpwm_unit_t mcpwm_unit; // MCPWM unit (0 or 1)
    mcpwm_timer_t timer;     // Timer (TIMER_0, TIMER_1, or TIMER_2)
    bool rampRate;
    int k_rampRate = 15;
    int motorSpeed;
};

#endif // MOTOR_H