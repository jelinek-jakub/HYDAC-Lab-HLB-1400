#include <Arduino.h>
#include <hlb1400.h>

HLB1400 hlb1400;

void setup() {
  Serial.begin(115200);
  Serial.print("Avalible flash size: ");
  Serial.print(ESP.getFlashChipSize()/1024/1024);
  Serial.println("MB");

  if (psramFound()) Serial.println("PSRAM: Found");
  else {
    Serial.println("PSRAM: Not found");
  }

  hlb1400.begin(Serial1, 32, 33, 25, 0);
}

void loop() 
{ 
  delay(2000);
  hlb1400.sendRequest(RequestType::Id);
  if(hlb1400.ReadResponse())
  {
    Serial.print("\nDevice ID: ");
    Serial.println(hlb1400.deviceId);

    delay(3000);
    while (true)
    {
      hlb1400.sendRequest(RequestType::Status);
      if(hlb1400.ReadResponse()) {
        Serial.print("\nStatus: ");
        Serial.println(hlb1400.deviceState);
      }

      hlb1400.sendRequest(RequestType::Data);
      if(hlb1400.ReadResponse()) {
  
        Serial.printf("Conductivity: %.1f µS/cm\n", hlb1400.Conductivity);
        Serial.printf("DC: %.2f %%\n", hlb1400.DC);
        Serial.printf("Saturation: %d %%\n", hlb1400.Saturation);
        Serial.printf("Temperature: %.1f °C\n", hlb1400.Temperature);
      }
      delay(5000);
    }
  }
  else
  {
    Serial.println("\nInvalide or no reponse from the senor.");
    delay(10000);
  }
}
  




