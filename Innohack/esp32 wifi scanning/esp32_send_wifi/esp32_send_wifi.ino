#include <WiFi.h>

const char* ssid = "esp";
const char* password = "12345678";
bool result;
void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_AP);

  result = WiFi.softAP(ssid, password, 6);

  if (result) {
    Serial.println("AP STARTED SUCCESSFULLY");
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("AP FAILED TO START");
  }
}

void loop() {
  if (result) {
    Serial.println("AP STARTED SUCCESSFULLY");
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("AP FAILED TO START");
  }
}
