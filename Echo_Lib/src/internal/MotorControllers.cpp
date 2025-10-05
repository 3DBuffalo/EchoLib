// MotorControllers.cpp
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

void MotorControllers::setAll(int percentage) {
    for (Motor& motor : motors) {
        motor.setSpeed(percentToCycle(percentage));
    }
}

void MotorControllers::stopAll() {
    for (Motor& motor : motors) {
        motor.setSpeed(0);
    }
}

void MotorControllers::set(int motor, int percentage) {
    Motor* targetMotor = getMotorById(motor);
    if (targetMotor) {
        targetMotor->setSpeed(percentToCycle(percentage));
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

int MotorControllers::percentToCycle(int percentage) {
    return (percentage * 255) / 100;
}   


Motor* MotorControllers::getMotorById(int id) {
    auto it = std::find_if(motors.begin(), motors.end(), [id](Motor& motor) {
        return motor.getId() == id;
    });
    return it != motors.end() ? &(*it) : nullptr;
}