#include "M5Atom.h"

void setup() {
  M5.begin(true, false, true);
  M5.IMU.Init();
  Serial.begin(115200);
  Serial.println("Initializing M5Stack Atom Matrix");
}

CRGB colors[] = {
  0xfe0000, // red
  0x1ED35E, // green
  0xDCDEE2 // white
};

float accX, accY, accZ;
int time_blink = 300;
int x, y, p;
int count = 0;
int state_on_off  = 0;

unsigned long timeSinceLastScreenRefresh;
unsigned long timeBtwScreenRefresh = 200;

//unsigned long timeSinceLastChipRefresh;
//unsigned long timeBtwChipRefresh = 10;


unsigned long time_milli;

void loop() {

  time_milli = millis();

  //checking for button being pressed
  if (M5.Btn.wasPressed()) {
    count++;
    Serial.println("Button was pressed");

  }

  M5.IMU.getAccelData(&accX, &accY, &accZ);

  // checking how many time the button was pressed
  switch (count) {

    // (i) all LEDs off
    case 0:
      M5.dis.clear();
      state_on_off = 0;
      break;

    // (ii) Manual Rear strobe (RED): LEDs strobe at a predetermined interval
    case 1:
      p = 0;
      if (state_on_off == 1) {
        for (x = 0; x < 5; x++) {
          for (y = 0; y < 5; y++) {
            M5.dis.drawpix(x, y, colors[p]);
          }
        }
      }
      break;

    case 2:
      // red
      p = 1;
      if (state_on_off == 1) {
        for (x = 0; x < 5; x++) {
          for (y = 0; y < 5; y++) {
            M5.dis.drawpix(x, y, colors[p]);
          }
        }
      }
      break;

    // Set LEDs for blinking red
    case 3:
      p = 1;
      if (state_on_off == 1) {
        for (x = 0; x < 5; x++) {
          for (y = 0; y < 5; y++) {
            M5.dis.drawpix(x, y, colors[p]);
          }
        }
      }
      if ((accZ > 1 || accZ < -1) && (state_on_off == 1)) {
        p = 1;
        for (x = 0; x < 5; x++) {
          for (y = 0; y < 5; y++) {
            M5.dis.drawpix(x, y, colors[p]);
          }
        }
        delay(1500); //we assume nothing is going on during a breaking, aka none is pressing anything

        delay(2000); //we assume nothign is going on during a breaking, aka none is pressing anything
      }
      break;

    // Set LEDs for blinking green
    case 4:
      p = 0;
     if (state_on_off == 1) {
        for (x = 0; x < 5; x++) {
          for (y = 0; y < 5; y++) {
            M5.dis.drawpix(x, y, colors[p]);
          }
        }
      }
      if ((accZ > 1 || accZ < -1) && (state_on_off == 1)) {
        p = 0;
        for (x = 0; x < 5; x++) {
          for (y = 0; y < 5; y++) {
            M5.dis.drawpix(x, y, colors[p]);
          }
        }
        delay(1500);
        delay(2000);
      }
      break;

    //count exceeded possible click options
    default:
      M5.dis.clear();
      state_on_off = 0;
      count = 0;
  }

  if (time_milli - timeSinceLastScreenRefresh > timeBtwScreenRefresh) {
    if (state_on_off == 0) {

      state_on_off = 1;
    }
    else {
      state_on_off  = 0;
      M5.dis.clear();
    }
    Serial.print("state_on_off: ");
    Serial.println(state_on_off);
    M5.update();

    timeSinceLastScreenRefresh = time_milli;
    Serial.println(time_milli);
    Serial.print("count: ");
    Serial.println(count);
  }
}
