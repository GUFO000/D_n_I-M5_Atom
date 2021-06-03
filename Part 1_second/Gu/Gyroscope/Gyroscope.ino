#include "M5Atom.h"

bool face_down();

void setup() {
  M5.begin(true, true, true);
  M5.IMU.Init();
}

CRGB colors[] = {
  0xfe0000, // red
  0x1ED35E, // green
  0xFFFFFF // white
};

float accX, accY, accZ;
float gyroX, gyroY, gyroZ;
float ahrsX_pitch, ahrsY_roll, ahrsZ_yaw;
float temp;

int x, y, p;
int count = 0;
int state_on_off  = 0;
int Blink = 0;

//threshold for inclining the matrix
int thold = 17;
float acc_thold = 1.2;

unsigned long timeSinceLastScreenRefresh;
unsigned long timeBtwScreenRefresh = 100;

unsigned long timeSinceLastChipRefresh;
unsigned long timeBtwChipRefresh = 100;

unsigned long time_milli;

bool face_is_up  = false;
bool face_is_down = false;

void loop() {

  time_milli = millis();

  //Detect face up position
  if (face_up()) {
    state_on_off = 1;
    face_is_up  = true;
    face_is_down = false;
  }

  //Detect face down position
  if (face_down()) {
    state_on_off = 2;
    face_is_down = true;
    face_is_up = false;
  }

  //  if (face_down()) {
  //    state_on_off = 0;
  //  }


  switch (state_on_off) {

    //mode 0 is off
    case 0:
      M5.dis.clear();
      break;
      Blink = 0;

    //mode 1 is on choosing mode
    case 1:
      p = 0;
      for (x = 0; x < 5; x++) {
        for (y = 0; y < 5; y++) {
          M5.dis.drawpix(x, y, colors[p]);
        }
      }
      M5.update();
      Blink = 0;
      break;

    //mode 2, one mode is selected
    case 2:
      p = 1;
      for (x = 0; x < 5; x++) {
        for (y = 0; y < 5; y++) {
          M5.dis.drawpix(x, y, colors[p]);
        }
      }
      M5.update();
      Blink = 0;
      break;
  }

  if (time_milli - timeSinceLastScreenRefresh > timeBtwScreenRefresh) {
    M5.update();
    timeSinceLastScreenRefresh = time_milli;
    Serial.println("Screen updated----------------");
  }

  if (time_milli - timeSinceLastChipRefresh > timeBtwChipRefresh) {

    M5.IMU.getTempData(&temp);
    M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
    M5.IMU.getAccelData(&accX, &accY, &accZ);
    M5.IMU.getAhrsData(&ahrsX_pitch, &ahrsY_roll, &ahrsZ_yaw);

    // Serial.println("Coordinates");
    // Serial.println(gyroX);
    // Serial.println(gyroY);
    // Serial.println(gyroZ);

    //    Serial.print("ahrsX: ");
    //    Serial.print(ahrsX_pitch);
    //    Serial.print(", ahrsY: ");
    //    Serial.print(ahrsY_roll);
    //    Serial.print(", ahrsZ: ");
    //    Serial.println(ahrsZ_yaw);

    Serial.print("accX: ");
    Serial.print(accX);
    Serial.print(", acccY: ");
    Serial.print(accY);
    Serial.print(", accZ: ");
    Serial.println(accZ);

    timeSinceLastScreenRefresh = time_milli;
  }
}

bool face_down() {
  bool test = false;

  if ((abs(ahrsX_pitch) < thold) && (abs(ahrsY_roll) < thold)) {
    test = true;
  }
  if (test) {
    Serial.println("FACE dOWN DOWN DOWN DETECTED");
  }
  return test;
}

bool face_up() {
  bool test = false;
  float magnitude_acc = 0;

  if (M5.Btn.wasPressed()) {
    test = true;
  }
  if ((abs(ahrsX_pitch) < thold) && (abs(ahrsY_roll) > (180 - thold))) {
    test = true;
    Serial.println("triggered by ROTATING-----------------------------------------------------");
  }
  
  magnitude_acc = sqrt(accX * accX + accY * accY + accZ * accZ);

  Serial.print("The magnitude of the acceleration is: ");
  Serial.print(magnitude_acc);
  Serial.print(" acc_thold ");
  Serial.print(acc_thold);
  
  if (magnitude_acc > acc_thold) {
    test = true;
      Serial.println("triggered by ACCELERATION /////////////////////////////////////// ");
  }

  if (test) {
    Serial.println("FACE UP DETECTED");
  }
  return test;
}






//    if (Blink  == 1) {
//      if (state_on_off == 0) {
//        state_on_off = 1;
//        p = 1;
//        for (x = 0; x < 5; x++) {
//          for (y = 0; y < 5; y++) {
//            M5.dis.drawpix(x, y, colors[p]);
//          }
//        }
//      }
//      else {
//        state_on_off  = 0;
//        M5.dis.clear();
//      }
//    }
