#include "WiFiServer.h"

WiFiServerBridge::WiFiServerBridge(const char* _ssid, const char* _password, unsigned int _port)
  : ssid(_ssid), password(_password), localPort(_port), lastPacketTime(0),
    _isConnected(false), _debugMode(false), lastClientPort(0), _timeout(2000) {}

void WiFiServerBridge::begin() {
  WiFi.softAP(ssid, password);
  udp.begin(localPort);
  if (_debugMode) {
    Serial.println("WiFi Access Point started");
    Serial.print("SSID: ");
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
    lastClientIP = udp.remoteIP();
    lastClientPort = udp.remotePort();
    lastPacketTime = millis();
    _isConnected = true;

    char buffer[MAX_PACKET_SIZE + 1];
    int len = udp.read(buffer, MAX_PACKET_SIZE);
    if (len > 0) {
      buffer[len] = 0;
      receivedData = String(buffer);
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

  // Handle timeout / connection status
  if (_connectionDependentTimeout) {
    _isConnected = (WiFi.softAPgetStationNum() > 0);
    if (_debugMode && !_isConnected) Serial.println("No WiFi client connected");
  } else {
    if (_isConnected && millis() - lastPacketTime > _timeout) {
      _isConnected = false;
      if (_debugMode) Serial.println("Client connection timed out");
    }
  }
}

void WiFiServerBridge::sendData(const String& data) {
  if (!_isConnected) {
    if (_debugMode) Serial.println("Cannot send data: No client connected");
    return;
  }
  sendPacket(data);
}

void WiFiServerBridge::sendPacket(const String& data) {
  int dataLength = data.length();
  if (dataLength <= MAX_PACKET_SIZE) {
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
    // Split large strings into MAX_PACKET_SIZE chunks
    int packets = (dataLength + MAX_PACKET_SIZE - 1) / MAX_PACKET_SIZE;
    for (int i = 0; i < packets; i++) {
      int start = i * MAX_PACKET_SIZE;
      int end = min(start + MAX_PACKET_SIZE, dataLength);
      String chunk = data.substring(start, end);

      udp.beginPacket(lastClientIP, lastClientPort);
      udp.print(chunk);
      udp.endPacket();

      if (_debugMode) {
        Serial.print("Sent packet ");
        Serial.print(i + 1);
        Serial.print("/");
        Serial.print(packets);
        Serial.print(" - ");
        int len = chunk.length() < 50 ? chunk.length() : 50;
        Serial.println(chunk.substring(0, len) + (chunk.length() > 50 ? "..." : ""));
      }
      delay(10);  // brief delay between packets
    }
  }
}

String WiFiServerBridge::readData() {
  String tmp = receivedData;
  receivedData = "";  // clear after reading
  return tmp;
}

bool WiFiServerBridge::getStatus() const {
  return _isConnected;
}

void WiFiServerBridge::enableDebug(bool enable) {
  _debugMode = enable;
}

void WiFiServerBridge::setTimeout(unsigned long ms) {
  _timeout = ms;
}

void WiFiServerBridge::setTimeoutConnectionDependent(bool enable) {
  _connectionDependentTimeout = enable;
}
