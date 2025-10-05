#ifndef WIFISERVER_H
#define WIFISERVER_H

#include <WiFi.h>
#include <WiFiUdp.h>

class WiFiServerBridge {
private:
    const char* ssid;
    const char* password;
    WiFiUDP udp;
    unsigned int localPort;
    unsigned long lastPacketTime;
    String receivedData;
    IPAddress lastClientIP;
    uint16_t lastClientPort;
    bool _isConnected;
    bool _debugMode;
    
    // Packet management
    static const int MAX_PACKET_SIZE = 1400; // Safe UDP packet size
    void sendPacket(const String& data);

public:
    WiFiServerBridge(const char* _ssid, const char* _password, unsigned int _port);
    
    void begin();
    void sendData(const String& data);
    String readData();
    bool getStatus() const;
    void enableDebug(bool enable);
    void processIncoming(); // Should be called in loop()
};

#endif