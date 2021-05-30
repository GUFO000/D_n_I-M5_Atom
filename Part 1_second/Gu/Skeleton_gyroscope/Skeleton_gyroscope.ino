#include "M5Atom.h"

bool Delay();

void setup() {
  M5.begin(true, true, true);
  M5.IMU.Init();
  //Serial.begin(115200);
  Serial.println("Initializing M5Stack Atom Matrix");
}

CRGB colors[] = {
  0xfe0000, // red
  0x1ED35E, // green
  0xff0000 // red
};

float accX, accY, accZ;
float gyroX, gyroY, gyroZ;
float ahrsX, ahrsY, ahrsZ;
float temp;


int time_blink = 300;
int x, y, p;
int count=0;
bool Blink = 0;

void loop() {

  M5.IMU.getTempData(&temp);
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  M5.IMU.getAhrsData(&ahrsX, &ahrsY, &ahrsZ);

  //  Serial.println("Coordinates");
  //  Serial.println(gyroX);
  //  Serial.println(gyroY);
  //  Serial.println(gyroZ);

  //  Serial.println(ahrsX);
  //  Serial.println(ahrsY);
  //  Serial.println(ahrsZ);


  //check if any condition is true
  if (check_from_sleep()) {
    count = 1;
  }
  else {
    count = 0;
  }

  //check if there was a valid conditio
  //change state from sleep if needed
  if (count == 0) {
    M5.dis.clear();
  }
  else if (count == 1 ) {
    p = 1;

    for (x = 0; x < 5; x++) {
      for (y = 0; y < 5; y++) {
        M5.dis.drawpix(x, y, colors[p]);
      }
    }
  }
  else {
    count = 0;
    Serial.println("There has been a mistake");
  }

  if(Delay(1000)){
    count = 1;
    }
    
  M5.update();
  delay(50);
}

//wait while executing bg checks
bool Delay(int num) {
  bool check_pressed = 0;
  int time_passed = 0;

  while (check_pressed != 1 && time_passed < num) {
    if (check_from_sleep()) {
      check_pressed = 1;
    }

    delay(10);
    time_passed = time_passed + 10;
    //    Serial.println("This is the time passed so far");
    //    Serial.println(time_passed);
    //    Serial.println("This is the check");
    //    Serial.println(check_pressed);
    M5.update();
    if (check_pressed) {
      break;
    }
  }
  return check_pressed;
}

//different test that need to be performed while waiting
bool check_from_sleep() {
  bool test  = false;
  Serial.println(accZ);
  Serial.println(ahrsY);

  if (M5.Btn.wasPressed()) {
    test = true;
  }
  if (ahrsY < -170) {
    test = true;
  }
//  if (accZ > 0.1) {
//    test = true;
//  }
  return test;
}
