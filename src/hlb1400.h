#ifndef HLB1400_H
#define HLB1400_H

#include <Arduino.h>

enum class RequestType {
  Id,
  Status,
  Data
};

class HLB1400 {
  public:
    HLB1400();
    void begin(HardwareSerial& serial, int rxPin, int txPin);
    void begin(HardwareSerial& serial, int rxPin, int txPin, int _dePin, int _rePin);
    void sendRequest(RequestType type);
    bool ReadResponse();
    void PrintFrameHEX(Stream& port);

    char deviceId[20];
    char deviceState[32];

    float Conductivity;
    float DC;
    int Saturation;
    float Temperature;

  private:
    int dePin = 0;
    int rePin = 0;
    HardwareSerial* _serial = nullptr;
    const byte _requestData[6]  = { 0x02, 0x02, 0x2B, 0x03, 0xCF, 0x03 };
    const byte _requestState[6] = { 0x02, 0x02, 0x2B, 0x01, 0xD1, 0x03 };
    const byte _requestID[6]    = { 0x02, 0x02, 0x2B, 0x00, 0xD2, 0x03 };
    byte recvBufferArray[30] = {};
};

#endif