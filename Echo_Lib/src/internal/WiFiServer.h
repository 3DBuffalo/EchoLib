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
    unsigned long _timeout; // configurable connection timeout in ms
    bool _connectionDependentTimeout = false;


    static const int MAX_PACKET_SIZE = 1400; // Safe UDP packet size
    void sendPacket(const String& data);

public:
    WiFiServerBridge(const char* _ssid, const char* _password, unsigned int _port);

    void begin();
    void processIncoming();           // call in loop()
    void sendData(const String& data); // send raw string
    String readData();                 // returns last received packet
    bool getStatus() const;            // connection status
    void enableDebug(bool enable);     // toggle debug prints
    void setTimeout(unsigned long ms); // configure connection timeout
    void setTimeoutConnectionDependent(bool enable); 

};
#endif
