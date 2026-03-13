
void setup() {
  Serial.begin(9600);     // HC-05 default baud rate
  Serial.println("Bluetooth Ready");
}

void loop() {
  for(int i = 0; i<10; i++){
    Serial.println(i);
    delay(1000);
  }
}
