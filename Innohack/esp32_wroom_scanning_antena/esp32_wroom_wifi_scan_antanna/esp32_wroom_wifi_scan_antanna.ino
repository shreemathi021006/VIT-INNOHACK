#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("ESP32 WiFi Scanner Started");

  // Set WiFi to station mode
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void loop() {
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
    }
  }

  Serial.println("-----------------------------");
  delay(3000); // scan every 3 seconds
}
