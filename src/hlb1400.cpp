#include "HLB1400.h"

HLB1400::HLB1400() {}

void HLB1400::begin(HardwareSerial& serial, int rxPin, int txPin) {
  _serial = &serial;
  _serial->begin(9600, SERIAL_8N1, rxPin, txPin);
}

void HLB1400::begin(HardwareSerial& serial, int rxPin, int txPin, int _dePin, int _rePin) {
  _serial = &serial;
  _serial->begin(9600, SERIAL_8N1, rxPin, txPin);

  dePin = _dePin;
  rePin = _rePin;

  if(dePin != 0) {
    pinMode(dePin,OUTPUT);
    digitalWrite(dePin, LOW);
  }
  if(rePin != 0) {
    pinMode(rePin,OUTPUT);
    digitalWrite(rePin, LOW);
  }
}

void HLB1400::sendRequest(RequestType type) {
  if(dePin != 0) digitalWrite(dePin, HIGH);
  if(rePin != 0) digitalWrite(rePin, HIGH);
  delay(10);

  if (!_serial) return;

  switch (type) {

     case RequestType::Id:
      _serial->write(_requestID, sizeof(_requestID));
      break;

    case RequestType::Status:
      _serial->write(_requestState, sizeof(_requestState));
      break;

    case RequestType::Data:
      _serial->write(_requestData, sizeof(_requestData));
      break;

    default:
      break;
  }

  delay(6);
  delayMicroseconds(500);
  if(dePin != 0) digitalWrite(dePin, LOW);
  if(rePin != 0) digitalWrite(rePin, LOW);
  delay(25);
}

bool HLB1400::ReadResponse() {
  memset(recvBufferArray, 0, sizeof(recvBufferArray));

  if(_serial->available())
  {
    delay(50);

    if (_serial->peek() != 0x02)  {
      while (_serial->available()) _serial->read(); //Invalide header, discard buffer
      return false;
    }

    int i = 0;
    while (_serial->available() > 0 && i < sizeof(recvBufferArray)) {
      recvBufferArray[i] = _serial->read(); i++;
    }

    if(recvBufferArray[2] != 0x2A) return false;            

    switch (recvBufferArray[3]) {
      case 0x00: // ID 
        if(recvBufferArray[21] == 0x03) {
          size_t j = 0;
          for (size_t i = 4; i < sizeof(recvBufferArray) && j < sizeof(deviceId) - 1; ++i) {
            char c = (char)recvBufferArray[i];
            if (c == 0x0D || c == 0x0A) break;
            deviceId[j++] = c;
          }
          deviceId[j] = '\0';
          return true;
        }
        break;
      case 0x01: // State
        if(recvBufferArray[24] == 0x03) {
          size_t j = 0;
          for (size_t i = 7; i < sizeof(recvBufferArray) && j < sizeof(deviceState) - 1; ++i) {
            char c = (char)recvBufferArray[i];
            if (c == 0x0D || c == 0x0A) break;
            deviceState[j++] = c;
          }
          deviceState[j] = '\0';          
          return true;
        }
      case 0x03: // Data
        if(recvBufferArray[17] == 0x03) {
          Conductivity = ( recvBufferArray[4] + ( recvBufferArray[5] << 8)) / 010.0;
          DC           = ( recvBufferArray[8] + ( recvBufferArray[9] << 8)) / 100.0;
          Saturation   = (recvBufferArray[12] + (recvBufferArray[13] << 8))        ;
          Temperature  = (recvBufferArray[14] + (recvBufferArray[15] << 8)) / 010.0;
          return true;
        }
        break;
      default:
        break;
    }
    return false;
  }
  return false;
}

void HLB1400::PrintFrameHEX(Stream& port) {
    for (int i = 0; i < sizeof(recvBufferArray); i++) { 
        if (recvBufferArray[i] < 0x10) port.print("0");
        port.print(recvBufferArray[i], HEX);
    }
    port.println();

}
