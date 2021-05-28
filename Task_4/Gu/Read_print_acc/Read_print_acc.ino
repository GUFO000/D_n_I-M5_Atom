#include "M5Atom.h"

int oldX, oldY;

void setup() {
  M5.begin(true, false, true);
  M5.IMU.Init();
  Serial.begin(115200);
  oldX = -1;
  oldY = -1;
  Serial.println("Initializing M5Stack Atom Matrix");
}


CRGB colors[] = {
  0xfe0000, // green
  0x1ED35E // red
};



void loop() {
  float accX, accY, accZ;
  int x, y, p;

  //Serial.println("Ciao ");

  M5.IMU.getAccelData(&accX, &accY, &accZ);


  //  x = constrain(accX * 5 + 2, 0, 4);
  //  y = constrain(accY * 5 + 2, 0, 4);
  //  x = constrain(accX * 5 + 3, 0, 4);
  //  y = constrain(accY * 5 + 3, 0, 4);
  //  if (oldX != x || oldY != y) {
  //    M5.dis.drawpix(oldX, oldY, 0x000000);
  //    M5.dis.drawpix(x, y, 0xffffff);


  if (accX > 0.5) {
    p = 0;
    for (x = 3; x < 5; x++) {
      for (y = 0; y < 5; y++) {
        M5.dis.drawpix(x, y, colors[p]);
      }
    }
  }
  else {
    p = 0;
    for (x = 0; x < 2; x++) {
      for (y = 0; y < 5; y++) {
        M5.dis.drawpix(x, y, colors[p]);
      }
    }
  }


  Serial.println("This was the new X position ");
  Serial.println(accX);
  Serial.println("This was the new Y position ");
  Serial.println(accY);

  M5.dis.clear();
  
  delay(2);
  

}
