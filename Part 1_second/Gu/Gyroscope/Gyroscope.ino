#include "M5Atom.h"

int oldX, oldY;
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

float temp;
int time_blink = 300;
int x, y, p;
int count = 0;
bool Blink = 0;

void loop() {


  M5.IMU.getTempData(&temp);
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);

  Serial.println(gyroX);
 Serial.println(gyroY);
  Serial.println(gyroZ);


  
  M5.update();
  delay(50);
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
