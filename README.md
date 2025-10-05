# EchoLib

A comprehensive robotics library for the Echo microcontroller, providing wireless communication, control systems, and timing utilities for Arduino-based robotics projects.

## Features

- **BLE Server** - Bluetooth Low Energy communication for mobile control
- **WiFi Server** - UDP-based wireless communication for high-bandwidth applications
- **PID Controller** - Precise feedback control for motors and systems
- **Timer** - Non-blocking timing for multi-tasking robotics

## Installation

1. Download the latest `EchoLib.zip` from the [releases page](https://github.com/3DBuffalo/EchoLib/releases)
2. Open Arduino IDE
3. Go to **Sketch → Include Library → Add .ZIP Library...**
4. Select the downloaded file and restart Arduino IDE

## Quick Example

```cpp
#include <EchoLib.h>

BLEServerWrapper ble("MyRobot");

void setup() {
    Serial.begin(115200);
    ble.begin();
    ble.connect();
}

void loop() {
    ble.loop();
    
    if (ble.getStatus()) {
        String command = ble.readData();
        if (command == "LED_ON") {
            digitalWrite(LED_BUILTIN, HIGH);
            ble.sendData("LED: ON");
        }
    }
}
```

## Documentation

Complete documentation is available on GitBook:

**📚 [View Full Documentation](https://your-gitbook-url.gitbook.io/echolib)**

## Requirements

- Echo Microcontroller 
- Arduino IDE 1.8.0+ or Arduino IDE 2.0+
- ESP32 Board Support installed

## License

MIT License - see [LICENSE](LICENSE) file for details.

---

**Echo** - Robotics made simple
