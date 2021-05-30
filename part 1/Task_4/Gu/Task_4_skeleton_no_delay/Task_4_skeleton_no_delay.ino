#include "M5Atom.h"

int oldX, oldY;
bool Delay();

void setup() {
  M5.begin(true, false, true);
  M5.IMU.Init();
  Serial.begin(115200);
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
int state_on_off  = 0;
bool Blink = 0;

unsigned long timeSinceLastScreenRefresh;
unsigned long timeBtwScreenRefresh = 200;

unsigned long timeSinceLastChipRefresh;
unsigned long timeBtwChipRefresh = 10;


unsigned long time_milli;

void loop() {

  time_milli = millis();
  //Serial.println(time_milli);

  //checking for button being pressed
  if (M5.Btn.wasPressed()) {

    //increase count but only 4 options available
    count++;
    Serial.println("Button was pressed");
  }

  M5.IMU.getAccelData(&accX, &accY, &accZ);
  //Serial.println(accZ);

  // checking how many time the button was pressed
  switch (count) {

    // (i) all LEDs off
    case 0:
      M5.dis.clear();
      //Blink  = 0;
      state_on_off = 0;
      break;

    // (ii) Manual Rear strobe (RED): LEDs strobe at a predetermined interval
    case 1:
      p = 0;
      //Blink  = 1;
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
      //Blink  = 1;
      if (state_on_off == 1) {
        for (x = 0; x < 5; x++) {
          for (y = 0; y < 5; y++) {
            M5.dis.drawpix(x, y, colors[p]);
          }
        }
      }
      break;


    case 3:
      // Set LEDs for blinking red
      p = 1;
      //Blink  = 1;

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
        //Blink = 0;
        delay(2000); //we assume nothign is going on during a breaking, aka none is pressing anything
      }
      break;

    case 4:
      // Set LEDs for blinking red
      p = 0;
      //Blink  = 1;

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
        //Blink = 0;
        delay(2000);
      }
      break;

    //count exceeded possible click options
    default:
      M5.dis.clear();
      //Blink  = 0;
      state_on_off = 0;
      count = 0;
  }

  if (time_milli - timeBtwScreenRefresh > timeSinceLastScreenRefresh) {
    if (state_on_off == 0) {

      state_on_off = 1;
    }
    else {
      state_on_off  = 0;
      M5.dis.clear();
    }
    Serial.println(state_on_off);
    Serial.println(time_milli);
    M5.update();

    timeSinceLastScreenRefresh = time_milli; 
    Serial.println(time_milli);
    Serial.println("count");
    Serial.println(count);
  }
}
