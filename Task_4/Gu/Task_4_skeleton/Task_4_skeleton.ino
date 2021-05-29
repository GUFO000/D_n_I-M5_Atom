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
  0xfe0000, // red
  0x1ED35E, // green
  0xff0000 // red
};

float accX, accY, accZ;
int x, y, p;
int count = 0;


void loop() {

  //checking for button being pressed
  if (M5.Btn.wasPressed()) {

    //increase count but only 4 options available
    count++;
    Serial.println("Button was pressed");
  }

  // checking how many time the button was pressed
  switch (count) {

    // (i) all LEDs off
    case 0:
      M5.dis.clear();
      break;

    // (ii) Manual Rear strobe (RED): LEDs strobe at a predetermined interval
    case 1:

      // red
      p = 0;
      for (x = 0; x < 5; x++) {
        for (y = 0; y < 5; y++) {
          M5.dis.drawpix(x, y, colors[p]);
        }
      }
      break;

    case 2:
      // red
      p = 1;
      for (x = 0; x < 5; x++) {
        for (y = 0; y < 5; y++) {
          M5.dis.drawpix(x, y, colors[p]);
        }
      }
      break;

      //count exceeded possible click options
    default:
      count = 0;

  }

  Serial.println(count);

  //M5.dis.clear();
  M5.update();
  delay(200);


}
