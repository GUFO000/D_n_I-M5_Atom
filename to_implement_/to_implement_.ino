
/*
#include "M5Atom.h"

int oldX, oldY;

void setup() {
  M5.begin(true, false, true);
  M5.IMU.Init();
  oldX = -1;
  oldY = -1;
}

void loop() {
  float accX, accY, accZ;
  int x, y;

  M5.IMU.getAccelData(&accX, &accY, &accZ);
  x = constrain(accX * 5 + 2, 0, 4);
  y = constrain(accY * 5 + 2, 0, 4);
  if (oldX != x || oldY != y) {
    M5.dis.drawpix(oldX, oldY, 0x000000);
    M5.dis.drawpix(x, y, 0xffffff);
    oldX = x;
    oldY = y;
  }
}
*/



#include "M5Atom.h"

int oldX, oldY;

void setup() {
  M5.begin(true, false, true);
  M5.IMU.Init();
  oldX = -1;
  oldY = -1;
}

void loop() {
  float accX, accY, accZ;
  int x, y;

  M5.IMU.getAccelData(&accX, &accY, &accZ); // the function to get acceleration data 
  
  //x = constrain(accX * 5 + 2, 0, 4 ); //conditions de x axis 
  //y = constrain(accY * 5 + 2, 0, 4); //condition de y axis 
  
if (accX != 0 || accY != 0 ){

// oldx <=0 
 
  if (oldX != x || oldY != y) {
    //M5.dis.drawpix(oldX, oldY, 0x000000);
    M5.dis.drawpix(oldX, oldY, 0xffffff);
    M5.dis.drawpix(0xffffff,0xffffff, 0xffffff);
    oldX = x;
    oldY = y;
  }
}
delay(400);
M5.update();

}
