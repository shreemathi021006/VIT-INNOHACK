#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);   // ESP32 as scanner
  WiFi.disconnect();    // ensure clean start

  Serial.println("WiFi Signal Scan Started...");
}

void loop() {
  int n = WiFi.scanNetworks();

  if (n == 0) {
    Serial.println("No signals found");
  } else {
    Serial.print(n);
    Serial.println(" signals detected:");

    for (int i = 0; i < n; i++) {
      Serial.print("SSID: ");
      Serial.print(WiFi.SSID(i));

      Serial.print(" | RSSI: ");
      Serial.print(WiFi.RSSI(i));

      Serial.print(" dBm | Channel: ");
      Serial.print(WiFi.channel(i));

      Serial.print(" | Encryption: ");
      Serial.println(WiFi.encryptionType(i));
    }
  }

  Serial.println("-------------------------");
  delay(5000);   // scan every 5 seconds
}
