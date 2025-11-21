#include <EchoLib.h>

WiFiServerBridge wifi("EchoRobot", "password123", 8888);

void setup() {
    Serial.begin(115200);
    wifi.begin();
}

void loop() {
    wifi.processIncoming();
}