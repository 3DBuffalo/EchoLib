#include "MotorControllers.h"
#include "ServoDriver.h"

// Create the MotorControllers object
MotorControllers motorController;
ServoDriver servoDriver;

void setup() {
  // Initialize all motors to stopped state
  motorController.stopAll();
  Serial.begin(15200);
  delay(2000);
  servoDriver.init();
  //servoDriver.setAllZero();
  Serial.println("Motors initialized and stopped.");
}

void loop() {
  // Step 1: Set motors 1, 2, 5, and 6 to 50% power for 3 seconds
  //motorController.set(1, 50);
  //motorController.set(2, 50);
  //motorController.set(5, 50);
  //motorController.set(6, 50);
  //Serial.println("Motors 1, 2, 5, and 6 set to 50% power.");
  
  //delay(3000); // Run the motors for 3 seconds

  // Step 2: Stop all motors for 5 seconds
 // motorController.stopAll();
  //Serial.println("All motors stopped.");
  servoDriver.setServoAngle(8, 40);
  delay(1000);
  servoDriver.setServoAngle(8, 60);
  
  delay(5000); // Stop all motors for 5 seconds
}
