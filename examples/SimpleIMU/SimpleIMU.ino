#include <EchoLib.h>

IMU imu;
unsigned long lastPrint = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing IMU...");
  
  imu.begin();  // Init and auto-calibrate gyro
  
  // Optional: calibrate accelerometer (keep sensor flat)
  Serial.println("Keep sensor flat for accel calibration...");
  delay(2000);
  imu.calibrateAccel();
  
  Serial.println("IMU ready!");
}

void loop() {
  // Get fused orientation
  float roll, pitch, yaw;
  imu.getOrientation(roll, pitch, yaw);
  
  // Get acceleration data
  float accelX = imu.getAccelXms();
  float accelY = imu.getAccelYms();
  float accelZ = imu.getAccelZms();
  
  // Get G-forces
  float gForceX = imu.getForceX();
  float gForceZ = imu.getForceZ();
  
  // Get absolute gyro angles
  float gyroAngleX = imu.getGyroXdeg();
  float gyroAngleZ = imu.getGyroZdeg();
  
  // Print everything every 200ms
  if (millis() - lastPrint > 200) {
    Serial.println("=== IMU Data ===");
    
    Serial.print("Orientation - Roll: ");
    Serial.print(roll, 1);
    Serial.print("° Pitch: ");
    Serial.print(pitch, 1);
    Serial.print("° Yaw: ");
    Serial.println(yaw, 1);
    
    Serial.print("Accel (m/s²) - X: ");
    Serial.print(accelX, 2);
    Serial.print(" Y: ");
    Serial.print(accelY, 2);
    Serial.print(" Z: ");
    Serial.println(accelZ, 2);
    
    Serial.print("G-Force - X: ");
    Serial.print(gForceX, 2);
    Serial.print("g Z: ");
    Serial.print(gForceZ, 2);
    Serial.println("g");
    
    Serial.print("Gyro Angles - X: ");
    Serial.print(gyroAngleX, 1);
    Serial.print("° Z: ");
    Serial.print(gyroAngleZ, 1);
    Serial.println("°");
    
    Serial.println();
    lastPrint = millis();
  }
  
  // Optional: Reset yaw if button pressed or after long operation
  // imu.reset();
}