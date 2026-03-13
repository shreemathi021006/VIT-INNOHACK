#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);            
  SerialBT.begin("ESP32_WROOM");  
  Serial.println("Bluetooth Ready");
}

void loop() {
  SerialBT.println("Hello from ESP32");
  delay(1000);
}
