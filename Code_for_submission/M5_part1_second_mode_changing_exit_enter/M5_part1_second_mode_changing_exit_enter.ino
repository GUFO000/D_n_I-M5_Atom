#include "M5Atom.h"
//#include <FastLED.h>

int zero[25] = {
  0, 1, 1, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 1, 1, 0};

int one[25] = {
  0, 0, 1, 0, 0,
  0, 1, 1, 0, 0,
  0, 0, 1, 0, 0,
  0, 0, 1, 0, 0,
  0, 1, 1, 1, 0};

int two[25] = {
  0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 1, 1, 1, 0,
  0, 1, 0, 0, 0,
  0, 1, 1, 1, 0};

int tre[25] = {
  0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 1, 1, 1, 0};

int four[25] = {
  0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 0, 0, 1, 0};

//---------------------------------------

bool face_down();
bool face_up();
int check_mode_switch();
bool enter_exit_mode();
void DisplayColor(int number[], int fillColor);


//Few colors available
CRGB colors[] = {
  0xfe0000, // red
  0x1ED35E, // green
  0xFFFFFF // white
};



//physical variables that the M5 can read
float accX, accY, accZ;
float ahrsX_pitch, ahrsY_roll, ahrsZ_yaw;
float temp;

//variables to identify LED on the matrix
int x, y;

//variable to select element from matrix of colors
int matrix_color = 0;

//Variable to keep track of the active mode
int active_mode = 0;

//int to store result of checking if mode was changed (funtion does not run twice)
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

//#define NUM_LEDS 25
//#define DATA_PIN 27
//
//int n;
//CRGB leds[NUM_LEDS];

unsigned long timeSinceLastDigitOnScreen;
unsigned long timeBtwDigitsOnScreen = 100;

unsigned long timeSinceLastModeButtonPress = 0;
unsigned long timeBtwLastModeButtonPress = 100;
unsigned long time_milli_lastButtonPress = 0;

bool MODE_DETECTING = false;
bool MODE_SET = false;

//-----------------------------------------------------------------

void setup() {
  M5.begin(true, true, true);
  M5.IMU.Init();
}

//-----------------------------------------------------------------

void loop() {
  //Update time
  time_milli = millis();

  //Detect face up position if m5 was down
  //if it was up skip this (do not check for face up)
  if (face_is_down && face_up()) {

    face_is_up  = true;
    face_is_down = false;

    //it was just woken up, so start from mode 0
    active_mode = 0;
    MODE_DETECTING = true;
    MODE_SET = false;
  }

  //Detect face down position
  if (face_is_up && face_down()) {

    face_is_down = true;
    face_is_up = false;

    M5.dis.clear();
    MODE_DETECTING = false;
    MODE_SET = false;
  }

  // if face is up check the mode (tapping)
  if (face_is_up && MODE_DETECTING) {

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

    Serial.print("Active mode ");
    Serial.println(active_mode);

    switch (active_mode) {

      //Show Active temperature + Units
      case 0:
        DisplayColor(zero, 1);
        break;

      //Show average of last 24 hours of temperature + Units
      case 1:
        DisplayColor(one, 1);
        break;

      //Show color scale of temperature range + current temperature as color
      case 2:
        DisplayColor(two, 1);
        break;

      //Show graph of temperature across a predefined range
      case 3:
        DisplayColor(tre, 1);
        break;

      //Change units
      case 4:
        DisplayColor(four, 1);
        break;
    }

    if(enter_exit_mode()){
        MODE_DETECTING = false;
        MODE_SET = true;
      }    
    }

    //in this if we will execute the different modes
    if (face_is_up && MODE_SET){
      switch(active_mode){
         case 0:
          DisplayColor(zero, 2);
          break; 
         case 1:
          DisplayColor(one, 2);
          break;
         case 2:
          DisplayColor(two, 2);
          break;
         case 3:
          DisplayColor(tre, 2);
          break;
         case 4:
          DisplayColor(four, 2);
          break; 
      }
      if(enter_exit_mode()){
        MODE_DETECTING = true;
        MODE_SET = false;
      } 
    }

/*  //Refresh screen after equal intervals
  if (time_milli - timeSinceLastScreenRefresh > timeBtwScreenRefresh) {
    M5.update();
    timeSinceLastScreenRefresh = time_milli;
    //Serial.println("Screen updated----------------");
  }*/

  //Refresh chip in equal intervals
  if (time_milli - timeSinceLastChipRefresh > timeBtwChipRefresh) {

    M5.IMU.getTempData(&temp);
    M5.IMU.getAccelData(&accX, &accY, &accZ);
    M5.IMU.getAhrsData(&ahrsX_pitch, &ahrsY_roll, &ahrsZ_yaw);

    timeSinceLastChipRefresh = time_milli;
  }
}

//-----------------------------------------------------------------

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

//-----------------------------------------------------------------

bool face_up() {
  bool test = false;
  float magnitude_acc = 0;
  M5.update();
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
    //Serial.println("triggered by ACCELERATION ");
  }

  if (test) {
    Serial.println("FACE UP DETECTED");
  }
  return test;
}

//-----------------------------------------------------------------

bool enter_exit_mode(){
  bool check = 0;
  M5.update();
  if (M5.Btn.wasPressed()) {

    if (time_milli - timeSinceLastModeButtonPress > timeBtwLastModeButtonPress) {
      timeSinceLastModeButtonPress  = time_milli;
      check = true;
    }
  }
  return check;
}

//-----------------------------------------------------------------

int check_mode_switch() {
  int mode_changed = 0;
  float magnitude_acc = 0;

//  Serial.print("The magnitude of the X acceleration is: ");
//  Serial.println(accX);

/*  if (M5.Btn.wasPressed()) {
    time_milli_press = millis();

    if (time_milli_press - time_milli_last_press > time_btw_btn_press) {
      //        Serial.print("Tempo passato ultimo tocco ");
      //        Serial.println((time_milli_press - time_milli_last_press));

      time_milli_last_press  = time_milli_press;
      mode_changed = 1;
    }
  }
  else*/ 
  
  if (((abs(accX) > 0.37) || (abs(accY) > 0.37)) || (abs(accX) > 0.37) && (abs(accY) > 0.37)) {
    time_milli_press = millis();

    if (time_milli_press - time_milli_last_press > time_btw_btn_press) {
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
}

void DisplayColor(int number[], int fillColor){
    M5.dis.clear();
    for (int i = 0; i < 25; i++)
    {   
        if(number[i] == 1){
        M5.dis.drawpix(i, colors[fillColor]);
        }
    }
}
