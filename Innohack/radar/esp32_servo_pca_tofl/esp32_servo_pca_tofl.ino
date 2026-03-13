#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_VL53L0X.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// Create a second I2C bus
TwoWire I2Ctwo = TwoWire(1);  

void setup() {
  Serial.begin(115200);

  // PCA9685 on default I2C (SDA=21, SCL=22)
  Wire.begin(); 
  pwm.begin();
  pwm.setPWMFreq(50);

  // VL53L0X on second I2C (SDA=19, SCL=18)
  I2Ctwo.begin(19,18);
  if (!lox.begin(0x29, &I2Ctwo)) {
    Serial.println("VL53L0X not detected!");
    while(1);
  }
  Serial.println("VL53L0X detected");
}

void loop() {
  // Your servo + measurement code
}
