import processing.serial.*;

Serial myPort;
float angle = 0;
float distance = 0;

int minValidDist = 0;   // STOP threshold in mm
int maxDistance  = 150;   // Radar max range (mm)
int radarRadius  = 350;   // Pixels for maxDistance

void setup() {
  size(800, 400);
  smooth();
  
  println("Available serial ports:");
  println(Serial.list());
  
  // Replace COM5 with your ESP32 COM port
  myPort = new Serial(this, "COM5", 115200);
  myPort.bufferUntil('\n');
}

void draw() {
  background(0);
  translate(width/2, height); // Radar at bottom-center
  
  drawRadar();
  drawSweepLine();
  drawObject();
  drawText();
}

// ---------------- SERIAL ----------------
void serialEvent(Serial myPort) {
  String data = myPort.readStringUntil('\n');
  if (data != null) {
    data = trim(data);
    if (data.startsWith("DATA")) {
      String[] parts = split(data, ',');
      if (parts.length == 3) {
        angle = float(parts[1]);
        distance = float(parts[2]);
      }
    }
  }
}

// ---------------- RADAR ----------------
void drawRadar() {
  stroke(0, 255, 0);
  noFill();
  
  // Distance arcs
  arc(0, 0, radarRadius*2, radarRadius*2, PI, TWO_PI);
  arc(0, 0, radarRadius*2*0.66, radarRadius*2*0.66, PI, TWO_PI);
  arc(0, 0, radarRadius*2*0.33, radarRadius*2*0.33, PI, TWO_PI);
  
  // Angle lines
  for (int a = 0; a <= 180; a += 30) {
    float x = cos(radians(a)) * radarRadius;
    float y = -sin(radians(a)) * radarRadius;
    line(0, 0, x, y);
  }
}

// ---------------- SWEEP ----------------
void drawSweepLine() {
  stroke(255);
  float x = cos(radians(angle)) * radarRadius;
  float y = -sin(radians(angle)) * radarRadius;
  line(0, 0, x, y);
}

// ---------------- OBJECT ----------------
void drawObject() {
  if (distance < minValidDist || distance > maxDistance) return; // Ignore below STOP
  
  stroke(255, 0, 0);
  fill(255, 0, 0);
  
  float r = map(distance, minValidDist, maxDistance, 0, radarRadius);
  float x = cos(radians(angle)) * r;
  float y = -sin(radians(angle)) * r;
  ellipse(x, y, 10, 10);
}

// ---------------- TEXT ----------------
void drawText() {
  fill(0, 255, 0);
  textSize(14);
  text("Angle: " + int(angle) + "°", -380, -380);
  text("Distance: " + int(distance) + " mm", -380, -360);
  
  if (distance < minValidDist) {
    fill(255, 0, 0);
    text("STATUS: STOP", -380, -340);
  } else {
    fill(0, 255, 0);
    text("STATUS: SCANNING", -380, -340);
  }
}
