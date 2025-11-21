#include "PIDController.h"
#include "Timer.h"
#include <math.h>

Timer timer;

PIDController::PIDController(float P, float I, float D, float kTarget, float kMaxTolerance, float kMinTolerance)
    : kP(P), kI(I), kD(D), target(kTarget), maxTolerance(kMaxTolerance), minTolerance(kMinTolerance) {
    
    maxTarget = target + maxTolerance;
    minTarget = target - minTolerance;
    timer.start();
    lastTimeStamp = timer.get(); // start reference
}

float PIDController::getOutput(float kSensorValue) {
    sensorValue = kSensorValue;

    unsigned long now = timer.get();
    float deltaTime = (now - lastTimeStamp) / 1000.0f; // convert ms to seconds
    if (deltaTime <= 0) deltaTime = 1e-3; // prevent div by zero

    error = target - sensorValue;

    // state flags
    greaterThanMax = sensorValue > target;
    lowerThanMin  = sensorValue < target;
    onTarget      = (sensorValue <= maxTarget && sensorValue >= minTarget);

    // Integrator with limit
    if (fabs(error) < iLimit) {
        errorSum += error * deltaTime;
    }

    // Derivative
    errorRate = (error - lastError) / deltaTime;

    // update memory
    lastTimeStamp = now;
    lastError = error;

    if(onTarget) return 0;

    // Output
    return (kP * error) + (kI * errorSum) + (kD * errorRate);
}

void PIDController::pause() {
    error = 0;
    errorRate = 0;
    errorSum = 0;
    timer.reset();
    timer.stop();
}

void PIDController::setNewTarget(float kTarget, float kMaxTolerance, float kMinTolerance) {
    target = kTarget;
    maxTolerance = kMaxTolerance;
    minTolerance = kMinTolerance;
    maxTarget = target + maxTolerance;
    minTarget = target - minTolerance;
}

void PIDController::setNewVals(float P, float I, float D){
    kP = P;
    kI = I;
    kD = D;
}

void PIDController::setIlimit(float kLim) {
    iLimit = kLim;
}

bool PIDController::isOnTarget(){
    return onTarget;
}
