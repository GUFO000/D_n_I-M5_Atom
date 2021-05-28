#include "M5Atom.h"

int oldX, oldY;

void setup() {
  M5.begin(true, false, true);
  M5.IMU.Init();
  Serial.begin(115200);
  oldX = -1;
  oldY = -1;
  Serial.println("");
  Serial.println("Initializing M5Stack Atom Matrix");
}

void loop() {
  float accX, accY, accZ;
  int x, y;

  //Serial.println("Ciao ");
  
  M5.IMU.getAccelData(&accX, &accY, &accZ);
//  x = constrain(accX * 5 + 2, 0, 4);
//  y = constrain(accY * 5 + 2, 0, 4);
x = constrain(accX * 5 + 3, 0, 4);
  y = constrain(accY * 5 + 3, 0, 4);
  if (oldX != x || oldY != y) {
    M5.dis.drawpix(oldX, oldY, 0x000000);
    M5.dis.drawpix(x, y, 0xffffff);
    oldX = x;
    oldY = y;
    Serial.println("This was the new X position ");
    Serial.println(accX);
    Serial.println("This was the new Y position ");
    Serial.println(accY);
  }
}
