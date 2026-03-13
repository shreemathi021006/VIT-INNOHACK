#include <WiFi.h>
#include <Adafruit_VL53L0X.h>
#include <Wire.h>
#include "BluetoothSerial.h"
Adafruit_VL53L0X lox;

BluetoothSerial SerialBT;
void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  Serial.println("VL53L0X ESP32 Test");
  Serial.println("ESP32 WiFi Scanner Started");

  // Set WiFi to station mode
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  // tofl setup
  
  if (!lox.begin(0x29, &Wire)) {
    Serial.println("FAILED to detect VL53L0X");
    while (1);
  }
  Serial.println("VL53L0X detected");
}

int rssi;
void wifi(){
  Serial.println("Scanning for WiFi networks...");
  int n = WiFi.scanNetworks();
  if (n == 0) {
    Serial.println("No WiFi networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; i++) {
      Serial.print(i + 1);
      Serial.print(". SSID: ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" | RSSI: ");
      Serial.print(WiFi.RSSI(i));
      Serial.print(" dBm");
      Serial.print(" | Channel: ");
      Serial.print(WiFi.channel(i));
      Serial.print(" | Encryption: ");
      Serial.println(WiFi.encryptionType(i) == WIFI_AUTH_OPEN ? "Open" : "Secured");
      delay(10);
       VL53L0X_RangingMeasurementData_t measure;
       lox.rangingTest(&measure, false);
       if (measure.RangeStatus != 4) {
          Serial.print("Distance: ");
          Serial.print(measure.RangeMilliMeter);
          Serial.println(" mm");
      if(measure.RangeMilliMeter<=100 && WiFi.RSSI(i)>=-50){
          Serial.print("STOP,");
          Serial.println(measure.RangeMilliMeter);
     }
      else{
          Serial.print("GO,");
          //Serial.println(",");
          Serial.println(measure.RangeMilliMeter);
    }
    delay(3000);
  } 
  else {
    Serial.println("Out of range");
  }
    }
  }
  Serial.println("-----------------------------");
}



void loop(){
  wifi();
  //tofl();
  delay(1000);
}
