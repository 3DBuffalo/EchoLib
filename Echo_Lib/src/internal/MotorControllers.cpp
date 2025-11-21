#include "MotorControllers.h"
#include <algorithm>

MotorControllers::MotorControllers() {
    motors = {
        Motor(MCPWM_UNIT_0, MCPWM_TIMER_0, 1, MOTOR_1_PIN_1, MOTOR_1_PIN_2),
        Motor(MCPWM_UNIT_0, MCPWM_TIMER_1, 2, MOTOR_2_PIN_1, MOTOR_2_PIN_2),
        Motor(MCPWM_UNIT_0, MCPWM_TIMER_2, 3, MOTOR_3_PIN_1, MOTOR_3_PIN_2),
        Motor(MCPWM_UNIT_1, MCPWM_TIMER_0, 4, MOTOR_4_PIN_1, MOTOR_4_PIN_2),
        Motor(MCPWM_UNIT_1, MCPWM_TIMER_1, 5, MOTOR_5_PIN_1, MOTOR_5_PIN_2),
        Motor(MCPWM_UNIT_1, MCPWM_TIMER_2, 6, MOTOR_6_PIN_1, MOTOR_6_PIN_2)
    };
}

void MotorControllers::shutDown() {
    stopAll();
    for (Motor& motor : motors) {
        motor.disablePWM();
    }
}

void MotorControllers::setAll(float percentage) {
    int16_t duty = percentToCycle(percentage);
    for (Motor& motor : motors) {
        motor.setSpeed(duty);
    }
}

void MotorControllers::stopAll() {
    for (Motor& motor : motors) {
        motor.setSpeed(0);
    }
}

void MotorControllers::set(int motor, float percentage) {
    Motor* targetMotor = getMotorById(motor);
    if (targetMotor) {
        int16_t duty = percentToCycle(percentage);
        targetMotor->setSpeed(duty);
    }
}

void MotorControllers::reverseAll() {
    for (Motor& motor : motors) {
        motor.reverseDirection();
    }
}

void MotorControllers::reverse(int motor) {
    Motor* targetMotor = getMotorById(motor);
    if (targetMotor) {
        targetMotor->reverseDirection();
    }
}

void MotorControllers::setCoast() {
    for (Motor& motor : motors) {
        motor.setCoastMode();
    }
}

void MotorControllers::setBrake() {
    for (Motor& motor : motors) {
        motor.setBrakeMode();
    }
}

int16_t MotorControllers::percentToCycle(float percentage) {
    if (percentage > 100.0f) percentage = 100.0f;
    if (percentage < -100.0f) percentage = -100.0f;
    return (int16_t)(percentage * 10.0f);
}  

Motor* MotorControllers::getMotorById(int id) {
    auto it = std::find_if(motors.begin(), motors.end(), [id](Motor& motor) {
        return motor.getId() == id;
    });
    return it != motors.end() ? &(*it) : nullptr;
}