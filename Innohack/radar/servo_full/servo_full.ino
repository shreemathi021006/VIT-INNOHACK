#include <ESP32Servo.h>

Servo myServo;

// Servo control
int servoAngle = 0;
int servoStep  = 2;
int servoDelay = 30;
bool sweeping  = false;

// Distance received from WROOM
int dist = 0;

void setup() {
  Serial.begin(115200);
  myServo.attach(13);   // GPIO 13 supports PWM
  Serial.println("READY");
}

void loop() {

  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    msg.trim();
    int commaIndex = msg.indexOf(',');
    if (commaIndex > 0) {
      String cmd = msg.substring(0, commaIndex);
      dist = msg.substring(commaIndex + 1).toInt();
      if (cmd == "GO") {
        sweeping = true;
      }
      else if (cmd == "STOP") {
        sweeping = false;
      }
    }
  }

  if (sweeping) {
    myServo.write(servoAngle);
    // Send ONE clean line to Python
    Serial.print("DATA,");
    Serial.print(servoAngle);
    Serial.print(",");
    Serial.println(dist);

    servoAngle += servoStep;

    if (servoAngle >= 180 || servoAngle <= 0) {
      servoStep = -servoStep;
    }

    delay(servoDelay);
  }
  else {
    Serial.print("DATA,");
    Serial.print(servoAngle);
    Serial.print(",");
    Serial.println(dist);
  }
}
