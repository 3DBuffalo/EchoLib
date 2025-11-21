#include <EchoLib.h>

ServoDriver servoDriver;

void setup() {
    servoDriver.init();
    
    // Start in "home" position
    servoDriver.setAllZero();
    delay(1000);
    
    Serial.begin(115200);
    Serial.println("Robot arm ready!");
}

void loop() {
    // Move to "grab" position
    servoDriver.setServoAngle(0, 45);  // Base rotation
    servoDriver.setServoAngle(1, 90);  // Shoulder
    servoDriver.setServoAngle(2, 135); // Elbow
    delay(2000);
    
    // Move to "lift" position
    servoDriver.setServoAngle(1, 45);  // Lift shoulder
    servoDriver.setServoAngle(2, 90);  // Straighten elbow
    delay(2000);
    
    // Return home
    servoDriver.setAllZero();
    delay(2000);
}