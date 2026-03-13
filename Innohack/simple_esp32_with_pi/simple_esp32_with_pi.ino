int pi = 25;

void setup() {
  Serial.begin(115200);
  pinMode(pi,OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  digitalWrite(pi,HIGH);
  Serial.println("high"); 
  delay(1000);
  digitalWrite(pi,LOW);
  Serial.println("low");
  delay(1000);
  // put your main code here, to run repeatedly:

}
