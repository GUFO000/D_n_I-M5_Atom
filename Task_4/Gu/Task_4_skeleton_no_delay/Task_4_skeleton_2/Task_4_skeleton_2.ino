#include "M5Atom.h"

int oldX, oldY;
bool Delay();

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
  0xDCDEE2 // blue
};

float accX, accY, accZ;
int time_blink = 300;
int x, y, p;
int count = 0;
bool Blink = 0;

void loop() {

  //checking for button being pressed
  if (M5.Btn.wasPressed()) {

    //increase count but only 4 options available
    count++;
    Serial.println("Button was pressed");
  }

  M5.IMU.getAccelData(&accX, &accY, &accZ);
  Serial.println(accZ);

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
      Blink  = 1;
      for (x = 0; x < 5; x++) {
        for (y = 0; y < 5; y++) {
          M5.dis.drawpix(x, y, colors[p]);
        }
      }
      break;

    case 2:
      // red
      p = 1;
      Blink  = 1;
      for (x = 0; x < 5; x++) {
        for (y = 0; y < 5; y++) {
          M5.dis.drawpix(x, y, colors[p]);
        }
      }
      break;


    case 3:
      // Set LEDs for blinking red
      p = 1;
      Blink  = 1;

      for (x = 0; x < 5; x++) {
        for (y = 0; y < 5; y++) {
          M5.dis.drawpix(x, y, colors[p]);
        }
      }
      if (accZ > 1 || accZ < -1) {
        p = 1;
        for (x = 0; x < 5; x++) {
          for (y = 0; y < 5; y++) {
            M5.dis.drawpix(x, y, colors[p]);
          }
        }
        Blink = 0;
        Delay(2000);
      }
      break;

    case 4:
      // Set LEDs for blinking red
      p = 0;
      Blink  = 1;

      for (x = 0; x < 5; x++) {
        for (y = 0; y < 5; y++) {
          M5.dis.drawpix(x, y, colors[p]);
        }
      }
      if (accZ > 1 || accZ < -1) {
        p = 0;
        for (x = 0; x < 5; x++) {
          for (y = 0; y < 5; y++) {
            M5.dis.drawpix(x, y, colors[p]);
          }
        }
        Blink = 0;
        Delay(2000);
      }
      break;


    //count exceeded possible click options
    default:
      count = 0;
  }

  //Serial.println(count);

  if (Blink) {
    //keep lights on and check button
    if (Delay(time_blink)) {
      count++;
    }

    //turn lights off
    M5.dis.clear();

    //wait with light off while checking button
    if (Delay(time_blink - 2)) {
      count++;
    }

    //reset to false
    //Blink = 0;
  }
  else {
    M5.dis.clear();
  }

  M5.update();

  if (Delay(200)) {
    count++;
  }
}


bool Delay(int num) {
  bool check_pressed = 0;
  int time_passed = 0;

  while (check_pressed != 1 && time_passed < num) {
    if (M5.Btn.wasPressed()) {
      check_pressed = 1;

    }
    delay(10);
    time_passed = time_passed + 10;

    //    Serial.println("This is the time passed so far");
    //    Serial.println(time_passed);
    //    Serial.println("This is the check");
    //    Serial.println(check_pressed);

    M5.update();
  }
  return check_pressed;
}
