#include "M5Atom.h"

bool face_down();

int check_mode_switch();

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
float ahrsX_pitch, ahrsY_roll, ahrsZ_yaw;
float temp;

//variables to identify LED on the matrix
int x, y;

//variable to select element from matrix of colors
int matrix_color = 0;

int active_mode = 0;

int store_mode =  0;
//int state_on_off  = 0;
int Blink = 0;

//threshold for inclining the matrix
int thold = 17; //degrees
float acc_thold = 1.2; //g (m*s^2)

//Defining refresh times
unsigned long timeSinceLastScreenRefresh;
unsigned long timeBtwScreenRefresh = 20;

unsigned long timeSinceLastChipRefresh;
unsigned long timeBtwChipRefresh = 20;

//Variable to keep track of time
unsigned long time_milli;

unsigned long time_milli_press;
unsigned long time_milli_last_press = 0;
unsigned long time_btw_btn_press = 350;

//Variable to monitor if M5 is face up or down
bool face_is_up  = true;
bool face_is_down = false;



#define SAMPLE_COUNT 64
#define BUFFER_SIZE SAMPLE_COUNT

float bufferX[BUFFER_SIZE];
int counter = 0;

void loop() {

  //Update time
  time_milli = millis();

  //Detect face up position if m5 was down
  //if it was up skip this
  if (face_is_down && face_up()) {
    //state_on_off = 1;

    face_is_up  = true;
    face_is_down = false;

    //it was just woken up, so start from mode 0
    active_mode = 0;
  }

  //Detect face down position
  if (face_is_up && face_down()) {
    //state_on_off = 2;
    face_is_down = true;
    face_is_up = false;

    M5.dis.clear();
    //Blink = 0;
  }

  // if face is up check the mode (tapping)
  if (face_is_up) {
    store_mode  = check_mode_switch();

    //    Serial.print("check_mode_switch() ");
    //    Serial.println(store_mode);

    //get the mode modulus 4 (5 possible modes)
    if (((active_mode + store_mode) % 5) < 0) {
      active_mode = 5 + ((active_mode + store_mode) % 5);
    }
    else {
      active_mode = (active_mode + store_mode) % 5;
    }

//    Serial.print("Active mode ");
//    Serial.println(active_mode);

    switch (active_mode) {

      //Show Active temperature + Units
      case 0:
        M5.dis.clear();

        matrix_color = 0;
        for (x = 0; x < 1; x++) {
          for (y = 0; y < 5; y++) {
            M5.dis.drawpix(x, y, colors[matrix_color]);
          }
        }
        break;

      //Show average of last 24 hours of temperature + Units
      case 1:

        matrix_color = 1;
        M5.dis.clear();

        for (x = 0; x < 2; x++) {
          for (y = 0; y < 5; y++) {
            M5.dis.drawpix(x, y, colors[matrix_color]);
          }
        }
        break;

      //Show color scale of temperature range + current temperature as color
      case 2:

        matrix_color = 2;
        M5.dis.clear();

        for (x = 0; x < 3; x++) {
          for (y = 0; y < 5; y++) {
            M5.dis.drawpix(x, y, colors[matrix_color]);
          }
        }

        //Blink = 0;
        break;

      //Show graph of temperature across a predefined range
      case 3:

        matrix_color = 0;
        M5.dis.clear();

        for (x = 0; x < 4; x++) {
          for (y = 0; y < 5; y++) {
            M5.dis.drawpix(x, y, colors[matrix_color]);
          }
        }

        break;

      //Change units
      case 4:

        matrix_color = 1;
        M5.dis.clear();

        for (x = 0; x < 5; x++) {
          for (y = 0; y < 5; y++) {
            M5.dis.drawpix(x, y, colors[matrix_color]);
          }
        }

        //M5.update();
        break;
    }
  }


  //Refresh screen after equal intervals
  if (time_milli - timeSinceLastScreenRefresh > timeBtwScreenRefresh) {
    M5.update();
    timeSinceLastScreenRefresh = time_milli;
    //Serial.println("Screen updated----------------");
  }

  //Refresh chip in equal intervals
  if (time_milli - timeSinceLastChipRefresh > timeBtwChipRefresh) {

    M5.IMU.getTempData(&temp);
    M5.IMU.getAccelData(&accX, &accY, &accZ);
    M5.IMU.getAhrsData(&ahrsX_pitch, &ahrsY_roll, &ahrsZ_yaw);
    
    bufferX[counter] = accX;
    counter = (counter + 1)% BUFFER_SIZE;
    
    timeSinceLastChipRefresh = time_milli;
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

  if (magnitude_acc > acc_thold) {
    test = true;
    //Serial.println("triggered by ACCELERATION /////////////////////////////////////// ");
  }

  if (test) {
    Serial.println("FACE UP DETECTED");
  }
  return test;
}

int check_mode_switch() {
  int mode_changed = 0;
  float magnitude_acc = 0;

  Serial.print("The magnitude of the X acceleration is: ");
  Serial.println(accX);
  //    Serial.print(" acc_Y ");
  //    Serial.println(accY);


  //tap from right to left

  if (M5.Btn.wasPressed()) {
    time_milli_press = millis();

    if (time_milli_press - time_milli_last_press > time_btw_btn_press) {
      //        Serial.print("Tempo passato ultimo tocco ");
      //        Serial.println((time_milli_press - time_milli_last_press));

      time_milli_last_press  = time_milli_press;
      mode_changed = 1;
    }
  }
  else if (((abs(accX) > 0.37) || (abs(accY) > 0.37)) || (abs(accX) > 0.37) && (abs(accY) > 0.37)) {
    time_milli_press = millis();

    if (time_milli_press - time_milli_last_press > time_btw_btn_press) {
      //        Serial.print("Tempo passato ultimo tocco ");
      //        Serial.println((time_milli_press - time_milli_last_press));

      time_milli_last_press  = time_milli_press;


      if (accX > 0) {
        mode_changed = -1;
        Serial.println("Tap from the right");
      }
      else {
        mode_changed = 1;
        Serial.println("Tap from the left");
      }
    }
  }

  return mode_changed;
  //chenged
}
