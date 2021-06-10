#include "M5Atom.h"

int oldX, oldY;
bool Delay();

void setup() {
  M5.begin(true, true, true);
  M5.IMU.Init();
  Serial.begin(115200);
  Serial.println("Initializing M5Stack Atom Matrix");
}

CRGB colors[] = {
  0xfe0000, // red
  0x1ED35E, // green
  0xff0000 // red
};

float accX, accY, accZ;
float temp;
int time_blink = 300;
int x, y, p;
int count = 0;
bool Blink = 0;

void loop() {

//  //checking for button being pressed
//  if (M5.Btn.wasPressed()) {
//
//    //increase count but only 4 options available
//    count++;
//    Serial.println("Button was pressed");
//  }
//
//  // checking how many time the button was pressed

  M5.IMU.getTempData(&temp);


  Serial.println(temp);

  if (Blink) {
    if(Delay(time_blink)){
      count++;
      }
    M5.dis.clear();
    if(Delay(time_blink - 200)){
      count++;
      }
    Blink = 0;
  }
  else {
    M5.dis.clear();
  }

  M5.update();
  if(Delay(200)){
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
