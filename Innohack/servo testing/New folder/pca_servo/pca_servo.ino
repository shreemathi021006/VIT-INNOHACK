#include <Adafruit_PWMServoDriver.h>
#include<Wire.h>
Adafruit_PWMServoDriver pca;
int echo_1 = 8;
int trig_1 = 9;
long distance;

int pulse;
int angle = 0;

void setup() {
  Serial.begin(9600);
  pca.begin();
  pca.setPWMFreq(50);
  pinMode(echo_1, INPUT);
  pinMode(trig_1, OUTPUT);
  Serial.println("ultrasonic sensor started");
  // put your setup code here, to run once:

}
int  getd(){
  digitalWrite(trig_1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_1, LOW);

  // Measure echo
  long dur = pulseIn(echo_1, HIGH, 30000); // timeout = 30 ms
  if (dur==0){
    return 0;
  }
    else { distance = dur*0.034/2;
    return distance;}
   
}
void loop() {
  for( angle = 0; angle<180; angle+=5)
  {
    pulse = map(angle,0,180,150,600);
    pca.setPWM(0,0,pulse);
    Serial.println(angle);
    Serial.println(":");
    Serial.println(distance);
    delay(20);

  }
  for(angle=180; angle>0; angle-=5){
    pulse = map(angle,0,180,150,600);
    pca.setPWM(0,0,pulse);
    Serial.println(angle);
    Serial.println(":");
    Serial.println(distance);
    delay(20);
  
  }
  // put your main code here, to run repeatedly:

}
