#include "M5Atom.h"
#include <FastLED.H>

float oldX, oldY;

void setup() {
  M5.begin(true, false, true);
  M5.IMU.Init();
  Serial.begin(115200);
  oldX = -1;
  oldY = -1;
  Serial.println("");
  Serial.println("Initializing M5Stack Atom Matrix");
  
}
int a, b;
void loop() {
  float accX, accY, accZ;
  int x, y;
  

  //Serial.println("Ciao ");
  
  M5.IMU.getAccelData(&accX, &accY, &accZ);
//  x = constrain(accX * 5 + 2, 0, 4);
//  y = constrain(accY * 5 + 2, 0, 4);
x = constrain(accX * 5 + 3, 0, 4);
  y = constrain(accY * 5 + 3, 0, 4);

if ( accX <=0.5 && accY<=0.5 && oldX <=0)

{ 
  
  for (a=0;a<5;a++)
  { for (b= 0 ; b < 5; b++)
  {M5.dis.drawpix (a,b, 0xffffff);
  }
  }
}

else if (accX <=0.5 && accY<=0.5 && oldX>0)

{ 
  
  for (a=0;a<5;a++)
  { for (b = 0 ; b < 5;b++)
  {M5.dis.drawpix (a,b, 0x0080ff);
  }
  }
}
 oldX = accX;
 oldY = accY;
 M5.update();
}
