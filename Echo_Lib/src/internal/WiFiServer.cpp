#include "WiFiServer.h"

WiFiServerBridge::WiFiServerBridge(const char* _ssid, const char* _password, unsigned int _port) 
    : ssid(_ssid), password(_password), localPort(_port), lastPacketTime(0), 
      _isConnected(false), _debugMode(false), lastClientPort(0) {
}

void WiFiServerBridge::begin() {
    WiFi.softAP(ssid, password);
    udp.begin(localPort);
    
    if (_debugMode) {
        Serial.println("WiFi Access Point started");
        Serial.print("Network: ");
        Serial.println(ssid);
        Serial.print("IP Address: ");
        Serial.println(WiFi.softAPIP());
        Serial.print("Listening on port: ");
        Serial.println(localPort);
    }
}

void WiFiServerBridge::processIncoming() {
    int packetSize = udp.parsePacket();
    if (packetSize > 0) {
        // Update connection status and client info
        _isConnected = true;
        lastClientIP = udp.remoteIP();
        lastClientPort = udp.remotePort();
        lastPacketTime = millis();
        
        // Read the packet
        char incomingPacket[MAX_PACKET_SIZE + 1];
        int len = udp.read(incomingPacket, MAX_PACKET_SIZE);
        if (len > 0) {
            incomingPacket[len] = 0; // Null terminate
            receivedData = String(incomingPacket);
            
            if (_debugMode) {
                Serial.print("Received from ");
                Serial.print(lastClientIP);
                Serial.print(":");
                Serial.print(lastClientPort);
                Serial.print(" - ");
                Serial.println(receivedData);
            }
        }
    }
    
    // Check for connection timeout (2 seconds of no data)
    if (_isConnected && (millis() - lastPacketTime > 2000)) {
        _isConnected = false;
        if (_debugMode) {
            Serial.println("Client connection timed out");
        }
    }
}

void WiFiServerBridge::sendData(const String& data) {
    if (!_isConnected) {
        if (_debugMode) {
            Serial.println("Cannot send data: No client connected");
        }
        return;
    }
    
    sendPacket(data);
}

void WiFiServerBridge::sendPacket(const String& data) {
    int dataLength = data.length();
    
    if (dataLength <= MAX_PACKET_SIZE) {
        // Send as single packet
        udp.beginPacket(lastClientIP, lastClientPort);
        udp.print(data);
        udp.endPacket();
        
        if (_debugMode) {
            Serial.print("Sent to ");
            Serial.print(lastClientIP);
            Serial.print(":");
            Serial.print(lastClientPort);
            Serial.print(" - ");
            Serial.println(data);
        }
    } else {
        // Split into multiple packets for large data
        int packets = (dataLength + MAX_PACKET_SIZE - 1) / MAX_PACKET_SIZE;
        String packetId = String(millis()); // Simple packet ID
        
        for (int i = 0; i < packets; i++) {
            int start = i * MAX_PACKET_SIZE;
            int end = min(start + MAX_PACKET_SIZE, dataLength);
            String chunk = data.substring(start, end);
            
            // Format: MULTI:packetId:currentPacket:totalPackets:data
            String packet = "MULTI:" + packetId + ":" + String(i) + ":" + String(packets) + ":" + chunk;
            
            udp.beginPacket(lastClientIP, lastClientPort);
            udp.print(packet);
            udp.endPacket();
            
            if (_debugMode) {
                Serial.print("Sent packet ");
                Serial.print(i + 1);
                Serial.print("/");
                Serial.print(packets);
                Serial.print(" - ");
                Serial.println(chunk.substring(0, 50) + (chunk.length() > 50 ? "..." : ""));
            }
            
            delay(10); // Small delay between packets
        }
    }
}

String WiFiServerBridge::readData() {
    String data = receivedData;
    receivedData = ""; // Clear after reading
    return data;
}

bool WiFiServerBridge::getStatus() const {
    return _isConnected;
}

void WiFiServerBridge::enableDebug(bool enable) {
    _debugMode = enable;
}