#ifndef MOTOR_H
#define MOTOR_H
#include "driver/mcpwm.h"

class Motor {
public:
    Motor(mcpwm_unit_t unit, mcpwm_timer_t timer, int id, int pin1, int pin2);
    
    void setSpeed(int16_t dutyCycle);
    void reverseDirection();
    void disablePWM();
    void setCoastMode();
    void setBrakeMode();
    int getId() const;
    bool isReversed() const;
    
private:
    void applySpeed(int16_t dutyCycle); 
    
    int id;
    int pin1, pin2;
    bool reversed;
    mcpwm_unit_t mcpwm_unit;
    mcpwm_timer_t timer;
    int16_t currentSpeed;    
};

#endif // MOTOR_H