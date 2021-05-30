#include "M5Atom.h"

void setup() {
  M5.begin(true, true, true);
  M5.IMU.Init();
}

CRGB colors[] = {
  0xfe0000, // red
  0x1ED35E, // green
  0xff0000 // white
};

float accX, accY, accZ;
float gyroX, gyroY, gyroZ;
float ahrsX_pitch, ahrsY_roll, ahrsZ_yaw;

float temp;
int time_blink = 300;
int x, y, p;
int count = 0;
int state_on_off  = 0;


unsigned long timeSinceLastScreenRefresh;
unsigned long timeBtwScreenRefresh = 200;

unsigned long time_milli;

void loop() {

  time_milli = millis();

  M5.IMU.getTempData(&temp);
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);

  //Serial.println("Coordinates");
  //  Serial.println(gyroX);
  // Serial.println(gyroY);
  //  Serial.println(gyroZ);


  M5.IMU.getAhrsData(&ahrsX_pitch, &ahrsY_roll, &ahrsZ_yaw);
  Serial.print("ahrsX: ");
  Serial.print(ahrsX_pitch);
  Serial.print(", ahrsY: ");
  Serial.print(ahrsY_roll);
  Serial.print(", ahrsZ: ");
  Serial.println(ahrsZ_yaw);



  if (time_milli - timeBtwScreenRefresh > timeSinceLastScreenRefresh) {
    if (state_on_off == 0) {

      state_on_off = 1;
      p=1;
      for (x = 0; x < 5; x++) {
        for (y = 0; y < 5; y++) {
          M5.dis.drawpix(x, y, colors[p]);
        }
      }
    }
    else {
      state_on_off  = 0;
      M5.dis.clear();
    }

    M5.update();
    timeSinceLastScreenRefresh = time_milli;
  }
}
