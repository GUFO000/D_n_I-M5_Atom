#include "M5Atom.h"

int n, mat;
char string_temp[10];


int zero[25] = {
  0, 1, 1, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 1, 1, 0
};

int one[25] = {
  0, 0, 1, 0, 0,
  0, 1, 1, 0, 0,
  0, 0, 1, 0, 0,
  0, 0, 1, 0, 0,
  0, 1, 1, 1, 0
};

int two[25] = {
  0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 1, 1, 1, 0,
  0, 1, 0, 0, 0,
  0, 1, 1, 1, 0
};

int tre[25] = {
  0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 1, 1, 1, 0
};

int four[25] = {
  0, 1, 0, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 0, 0, 1, 0
};

int five[25] = {
  0, 1, 1, 1, 0,
  0, 1, 0, 0, 0,
  0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 1, 1, 1, 0
};

int six[25] = {
  0, 1, 0, 0, 0,
  0, 1, 0, 0, 0,
  0, 1, 1, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 1, 1, 0
};

int seven[25] = {
  0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 0, 0, 1, 0,
  0, 0, 0, 1, 0,
  0, 0, 0, 1, 0
};

int eight[25] = {
  0, 1, 1, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 1, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 1, 1, 0
};

int nine[25] = {
  0, 1, 1, 1, 0,
  0, 1, 0, 1, 0,
  0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
  0, 0, 0, 1, 0
};
int letter_c[25] = {
  0, 1, 1, 1, 0,
  1, 0, 0, 0, 0,
  1, 0, 0, 0, 0,
  1, 0, 0, 0, 0,
  0, 1, 1, 1, 0
};
int letter_f[25] = {
  0, 1, 1, 1, 0,
  0, 1, 0, 0, 0,
  0, 1, 1, 0, 0,
  0, 1, 0, 0, 0,
  0, 1, 0, 0, 0
};
//---------------------------------------

bool is_shaken();
int check_mode_switch();
bool set_timer();
void DisplayColor(int number[], int fillColor);
void print_digit(char digit);


//Few colors available
CRGB colors[] = {
  0xfe0000, // red
  0x1ED35E, // green
  0xFFFFFF, // white
  0x031cfc, // blue
  0x2090f7, //light blue
  0x137a10, //green
  0xc76316, // orange
  0xc71616, //red
};

//physical variables that the M5 can read
float accX, accY, accZ;
//float ahrsX_pitch, ahrsY_roll, ahrsZ_yaw;

//variables to identify LED on the matrix
int x, y;

//variable to select element from matrix of colors
int matrix_color = 0;

//threshold for inclining the matrix
int thold = 17; //degrees
float acc_thold = 1.3; //g (m*s^2)

//Variable to keep track of time
unsigned long time_milli;

unsigned long timeSinceLastChipRefresh;
unsigned long timeBtwChipRefresh = 20;

unsigned long time_milli_press;
unsigned long time_milli_last_press = 0;
unsigned long time_btw_btn_press = 350;

//Variable to monitor if M5 is face up or down
bool face_timer1  = true;
bool face_timer2 = false;

unsigned long timeSinceLastDigitOnScreen;
unsigned long timeBtwDigitsOnScreen = 100;

unsigned long timeSinceLastModeButtonPress = 0;
unsigned long timeBtwLastModeButtonPress = 100;
unsigned long time_milli_lastButtonPress = 0;

unsigned long time_btw_digitUpdate_mode0 = 600;
unsigned long time_last_digitUpdate_mode0 = 0;

bool TIME_SHOWING = false;
bool TIME_SETTING = false;

bool timer1_set = false;
bool timer2_set = false;

unsigned long initial_timer1;
unsigned long initial_timer2;

unsigned long time_left;

unsigned long len_timer1;
unsigned long len_timer2;

char time_to_print[20];


//-----------------------------------------------------------------

void setup() {
  M5.begin(true, false, true);
  M5.IMU.Init();
}

//-----------------------------------------------------------------

void loop() {
  //Update time
  time_milli = millis();

  /*
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

    }*/
  //Serial.println(accY);

  //check if timer 1 shoudl be shown
  if ((accY > 0.9)&& face_timer2) {
    DisplayColor(letter_f, 1);
    face_timer1 =true;
    face_timer2 =false;
  }

  //check if timer 1 shoudl be shown
  if(accY < -0.9)&& face_timer1){
    DisplayColor(zero, 1);
    face_timer1 =false;
    face_timer2 =true;
  }
  
  if(face_timer1){
    if(!timer1_set){
      
      set_timer();    
    }
    else{
      time_left = (time_milli - initial_time1)/60000;
      if (time_left >= len_timer1)
        //function to blink;
        DisplayColor(five, 2);
        n = 0;
        dtostrf(time_left, 5, 2, time_to_print);
      }
    //set
      //show time left
    
    }
  //if timer1 is set 
    //check time left timer 1
  //if timer2 is set
    //check time left timer 2

  if (TIME_SHOWING){
    if(face_timer1){
      time_left = (time_milli - initial_time1)/60000;
      dtostrf(time_left, 5, 2, time_to_print);
      if (time_milli - time_last_digitUpdate_mode0 > time_btw_digitUpdate_mode0) {
//          Serial.print("---------string tmp");
//          Serial.println(string_temp);
          if (n == strlen(time_to_print)) {
            n = 0;
            M5.dis.clear();
            //DisplayColor(letter_c, 1);
          }
          else {
            print_digit(time_to_print[n]);
            n++;
          }
          time_last_digitUpdate_mode0 = time_milli;
        }
    }
    
    }
  //Refresh chip in equal intervals
  if (time_milli - timeSinceLastChipRefresh > timeBtwChipRefresh) {

    M5.IMU.getAccelData(&accX, &accY, &accZ);
    //M5.IMU.getAhrsData(&ahrsX_pitch, &ahrsY_roll, &ahrsZ_yaw);

    timeSinceLastChipRefresh = time_milli;
  }
}

//-----------------------------------------------------------------

void set_timer1(unsigned long &initial_timer1){
  initial_timer1 = time_milli;
  timer1_set = true;
}

void set_timer2(unsigned long &initial_timer2){
  initial_timer2 = time_milli;
  timer1_set = true;
}

bool shaken() {
  bool test = false;
  float magnitude_acc = 0;

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

bool set_timer() {
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

void DisplayColor(int number[], int fillColor) {
  M5.dis.clear();
  for (int i = 0; i < 25; i++)
  {
    if (number[i] == 1) {
      M5.dis.drawpix(i, colors[fillColor]);
    }
  }
}

void print_digit(char digit) {
  if (digit == '0') {
    DisplayColor(zero, 1);
  }
  else if (digit == '1') {
    DisplayColor(one, 1);
  }
  else if (digit == '2') {
    DisplayColor(two, 1);
  }
  else if (digit == '3') {
    DisplayColor(tre, 1);
  }
  else if (digit == '4') {
    DisplayColor(four, 1);
  }
  else if (digit == '5') {
    DisplayColor(five, 1);
  }
  else if (digit == '6') {
    DisplayColor(six, 1);
  }
  else if (digit == '7') {
    DisplayColor(seven, 1);
  }
  else if (digit == '8') {
    DisplayColor(eight, 1);
  }
  else if (digit == '9') {
    DisplayColor(nine, 1);
  }
  else if (digit == '.') {
    M5.dis.clear();
    M5.dis.drawpix(22, colors[1] );
  }
}
