#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

class PIDController {
public:
  PIDController(float P, float I, float D, float kTarget, float kMaxTolerance, float kMinTolerance);

  float getOutput(float kSensorValue);

  void pause();

  void setNewTarget(float kTarget, float kMaxTolerance, float kMinTolerance);

  void setNewVals(float P, float I, float D);

  void setIlimit(float kLim);

  bool isOnTarget();

private:
  float kP = 0;
  float kI = 0;
  float kD = 0;

  float error;
  float output;
  float errorSum;
  float errorRate;
  float lastError;
  float lastTimeStamp;
  float currentTime;
  float sensorValue;

  float target;
  float iLimit;
  float maxTarget;
  float minTarget;

  float minTolerance;
  float maxTolerance;

  bool greaterThanMax = false;
  bool lowerThanMin = false;
  bool onTarget = false;
};

#endif // PIDCONTROLLER_H
