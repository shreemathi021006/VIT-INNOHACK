import processing.serial.*;

Serial myPort;
String data = "";
int angle = 0;
int distance = 0;

void setup() {
  size(800, 400);               // Half-screen
  smooth();
  myPort = new Serial(this, "COM8", 9600);
  myPort.bufferUntil('\n');
}

void draw() {
  background(0);
  translate(width/2, height);   // Bottom-center
  drawRadar();
  drawLine();
  drawObject();
}

void serialEvent(Serial myPort) {
  data = myPort.readStringUntil('\n');
  if (data != null) {
    data = trim(data);
    String[] parts = split(data, ',');
    if (parts.length == 2) {
      angle = int(parts[0]);
      distance = int(parts[1]);
    }
  }
}

void drawRadar() {
  stroke(0, 255, 0);
  noFill();

  // Range arcs
  for (int r = 100; r <= 400; r += 100) {
    arc(0, 0, r*2, r*2, PI, TWO_PI);
  }

  // Angle lines
  for (int a = 0; a <= 180; a += 30) {
    float x = 400 * cos(radians(a));
    float y = -400 * sin(radians(a));
    line(0, 0, x, y);
  }
}

void drawLine() {
  stroke(0, 255, 0);
  float x = 400 * cos(radians(angle));
  float y = -400 * sin(radians(angle));
  line(0, 0, x, y);
}

void drawObject() {
  if (distance > 0 && distance < 400) {
    stroke(255, 0, 0);
    float x = distance * cos(radians(angle));
    float y = -distance * sin(radians(angle));
    ellipse(x, y, 8, 8);
  }
}
