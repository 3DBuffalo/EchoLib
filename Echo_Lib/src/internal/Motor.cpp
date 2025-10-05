// Motor.cpp
#include <Arduino.h>
#include "Motor.h"
#include "MotorControllers.h"

// Constructor with initialization for MCPWM unit and timer
Motor::Motor(mcpwm_unit_t unit, mcpwm_timer_t timer, int id, int pin1, int pin2) : mcpwm_unit(unit), timer(timer), id(id), pin1(pin1), pin2(pin2), reversed(false) {
    mcpwm_io_signals_t signalA, signalB;
    
    // Map unit and timer to specific signals
    if (unit == MCPWM_UNIT_0) {
        if (timer == MCPWM_TIMER_0) {
            signalA = MCPWM0A;
            signalB = MCPWM0B;
        } else if (timer == MCPWM_TIMER_1) {
            signalA = MCPWM1A;
            signalB = MCPWM1B;
        } else if (timer == MCPWM_TIMER_2) {
            signalA = MCPWM2A;
            signalB = MCPWM2B;
        }
    } else if (unit == MCPWM_UNIT_1) {
        if (timer == MCPWM_TIMER_0) {
            signalA = MCPWM0A;
            signalB = MCPWM0B;
        } else if (timer == MCPWM_TIMER_1) {
            signalA = MCPWM1A;
            signalB = MCPWM1B;
        } else if (timer == MCPWM_TIMER_2) {
            signalA = MCPWM2A;
            signalB = MCPWM2B;
        }
    }

    // Initialize GPIO pins for PWM
    mcpwm_gpio_init(unit, signalA, pin1);
    mcpwm_gpio_init(unit, signalB, pin2);

    // Configure MCPWM
    mcpwm_config_t pwm_config = {
        .frequency = 1000,              // Set frequency
        .cmpr_a = 0,                         // Initial duty cycle of PWMxA = 0%
        .cmpr_b = 0,                         // Initial duty cycle of PWMxB = 0%
        .duty_mode = MCPWM_DUTY_MODE_0,      // Active HIGH
        .counter_mode = MCPWM_UP_COUNTER     // Up counter mode
    };
    mcpwm_init(unit, timer, &pwm_config);
}


// Set motor speed with direction handling
void Motor::setSpeed(int dutyCycle) {
    // Clamp dutyCycle between -100 and 100
    if (dutyCycle > 100) dutyCycle = 100;
    if (dutyCycle < -100) dutyCycle = -100;

    // Flip sign if reversed
    if (reversed) dutyCycle *= -1;

    if(dutyCycle == 0){
        mcpwm_set_duty(mcpwm_unit, timer, MCPWM_OPR_A, 0);
        mcpwm_set_duty(mcpwm_unit, timer, MCPWM_OPR_B, 0);
        delay(20);
    }else{

        if (dutyCycle > 0) {
            for(int i = 0; i < dutyCycle; i += k_rampRate){
                motorSpeed = i;
                if(abs(dutyCycle) - abs(motorSpeed) < k_rampRate) motorSpeed = dutyCycle;
                mcpwm_set_duty(mcpwm_unit, timer, MCPWM_OPR_A, dutyCycle);
                mcpwm_set_duty(mcpwm_unit, timer, MCPWM_OPR_B, 0);
                delay(20);
            }
        } else {
            for(int i = 0; i > dutyCycle; i -= k_rampRate){
                motorSpeed = i;
                if(abs(dutyCycle) - abs(motorSpeed) < k_rampRate) motorSpeed = dutyCycle;
                mcpwm_set_duty(mcpwm_unit, timer, MCPWM_OPR_B, -dutyCycle);
                mcpwm_set_duty(mcpwm_unit, timer, MCPWM_OPR_A, 0);
                delay(20);
            }
        }
    }
}


// Reverse motor direction
void Motor::reverseDirection() {
    reversed = !reversed;
}

// Disable PWM output
void Motor::disablePWM() {
    mcpwm_set_duty(mcpwm_unit, timer, MCPWM_OPR_A, 0);
    mcpwm_set_duty(mcpwm_unit, timer, MCPWM_OPR_B, 0);
}

// Set motor to coast mode
void Motor::setCoastMode() {
    disablePWM();
}

// Set motor to brake mode
void Motor::setBrakeMode() {
    mcpwm_set_signal_low(mcpwm_unit, timer, MCPWM_OPR_A);
    mcpwm_set_signal_low(mcpwm_unit, timer, MCPWM_OPR_B);
}

// Get motor ID
int Motor::getId() const {
    return id;
}

// Check if motor direction is reversed
bool Motor::isReversed() const {
    return reversed;
}
