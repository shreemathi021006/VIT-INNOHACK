#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox;

void setup() {
  Serial.begin(115200);

  // ESP32 I2C pins
  Wire.begin(21, 22);

  Serial.println("VL53L0X ESP32 Test");

  if (!lox.begin(0x29, &Wire)) {
    Serial.println("FAILED to detect VL53L0X");
    while (1);
  }

  Serial.println("VL53L0X detected");
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) {
    Serial.print("Distance: ");
    Serial.print(measure.RangeMilliMeter);
    Serial.println(" mm");
  } else {
    Serial.println("Out of range");
  }

  delay(200);
}
