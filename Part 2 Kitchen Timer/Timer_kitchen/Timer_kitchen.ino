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

int plus[25] = {
  0, 0, 0, 0, 0,
  0, 0, 1, 0, 0,
  0, 1, 1, 1, 0,
  0, 0, 1, 0, 0,
  0, 0, 0, 0, 0
};

int minus[25] = {
  0, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
  0, 1, 1, 1, 0,
  0, 0, 0, 0, 0,
  0, 0, 0, 0, 0
};

bool is_shaken();
int check_mode_switch();
bool set_timer();
void DisplayColor(int number[], int fillColor);
void print_digit(char digit);
void set_timer1(unsigned long &initial_t);

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

float accX, accY, accZ;
int x, y;

//variable to select element from matrix of colors
int matrix_color = 0;

//threshold for inclining the matrix
int thold = 17; //degrees
float acc_thold = 1.3; //g (m*s^2)

unsigned long time_milli;

unsigned long timeSinceLastChipRefresh = 0;
unsigned long timeBtwChipRefresh = 20;

unsigned long time_milli_last_press = 0;
unsigned long time_btw_btn_press = 350;

unsigned long timeSinceLastDigitOnScreen = 0;
unsigned long timeBtwDigitsOnScreen = 100;

unsigned long timeSinceLastModeButtonPress = 0;
unsigned long timeBtwLastModeButtonPress = 100;
unsigned long time_milli_lastButtonPress = 0;

unsigned long time_btw_digitUpdate_mode0 = 600;
unsigned long time_last_digitUpdate_mode0 = 0;


bool face_timer1  = true;
bool face_timer2 = false;

bool TIME_SHOWING = false;
bool TIME_SETTING = true;
bool TIME_BLINKING = false;


bool timer1_set = false;
bool timer2_set = false;

unsigned long initial_time1 = 0 ;
unsigned long initial_time2 = 0;

unsigned long len_timer1 = 20000; //120 000 is an exemple = start of the program
unsigned long len_timer2 = 10000;

int time_left1 = 1;
int time_left2 = 1;

char time_to_print[20];
int time_to_be_set = 0;

int blinking = 0;

//-----------------------------------------------------------------

void setup() {
  M5.begin(true, false, true);
  M5.IMU.Init();
}

//-----------------------------------------------------------------

void loop() {
  //Update time
  time_milli = millis();

  //  Serial.print("Face timer accY: ");  //check if timer 1 shoudl be shown

  if ((accY > 0.9) && face_timer2) {
    face_timer1 = true;
    face_timer2 = false;
  }

  //check if timer 2 shoudl be shown
  if ((accY < -0.9) && (face_timer1)) {
    face_timer1 = false;
    face_timer2 = true;
  }


  //Checking if any of the timers went off
  if (timer1_set) {
    time_left1 = (len_timer1 - time_milli + initial_time1) / 1000;
  }
  if (timer2_set) {
    time_left2 = (len_timer2 - time_milli + initial_time2) / 1000;
  }

  if (((time_left1 <= 0) && (time_left2 <= 0)) || (time_left1 <= 0) || (time_left2 <= 0)) {
    TIME_SHOWING = false;
    TIME_SETTING = false;
    TIME_BLINKING = true;
  }

  if (face_timer1 && (TIME_BLINKING == false)) {
    //    Serial.print(" 1");
    if (timer1_set) {
      TIME_SHOWING = true;
      TIME_SETTING = false;
      TIME_BLINKING = false;
      //Serial.println(" Time showing true");

    }
    else {
      TIME_SHOWING = false;
      TIME_SETTING = true;
      TIME_BLINKING = false;
      //Serial.println(" Time setting true");
    }
  }

  if (face_timer2 && (TIME_BLINKING == false)) {
    //    Serial.print(" 2");
    if (timer2_set) {
      TIME_SHOWING = true;
      TIME_SETTING = false;
      TIME_BLINKING = false;
    }
    else {
      TIME_SHOWING = false;
      TIME_SETTING = true;
      TIME_BLINKING = false;
    }
  }

  //  Serial.print("   MOde setting ");
  //  Serial.print(TIME_SETTING);
  //  Serial.print(", showing ");
  //  Serial.println(TIME_SHOWING);




  //-------------------------------------------
  if (TIME_SETTING) {

    if (face_timer1) {

      check_mode_switch();

      if (set_timer()) {
        len_timer1 = time_to_be_set * 60000;
        set_timer1(initial_time1) ;
        time_to_be_set = 0;
      }
    }

    if (face_timer2) {

      check_mode_switch();


      if (set_timer()) {
        len_timer2 = time_to_be_set * 60000;
        set_timer2(initial_time2) ;
        time_to_be_set = 0;
      }
    }
  }

  //-----------------------------------------

  if (TIME_SHOWING) {

    if (face_timer1) {
      //      Serial.print(" len_timer1 ");
      //      Serial.print(len_timer1);
      //      Serial.print(" inti time ");
      //      Serial.print(initial_time1);
      //      Serial.print(" Time milli ");
      //      Serial.print(time_milli);
      //      Serial.print(" Time left prima ");
      //      Serial.print(time_left);


      dtostrf(time_left1, 4, 0, time_to_print);
      if (time_milli - time_last_digitUpdate_mode0 > time_btw_digitUpdate_mode0) {

        Serial.print("---------string tp");
        Serial.println(time_to_print);

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

    if (face_timer2) {

      dtostrf(time_left2, 4, 0, time_to_print);

      if (time_milli - time_last_digitUpdate_mode0 > time_btw_digitUpdate_mode0) {

        Serial.print("---------string tp");
        Serial.println(time_to_print);
        
        if (n == strlen(time_to_print)) {
          n = 0;
          M5.dis.clear();
        }
        else {
          print_digit(time_to_print[n]);
          n++;
        }
        time_last_digitUpdate_mode0 = time_milli;
      }

    }
  }

  //----------------------------------------------

  if (TIME_BLINKING) {
    if (face_timer1) {

      timer1_set = false;
      time_left1 = 1;

      TIME_SHOWING = false;
      TIME_SETTING = false;

      if (time_milli - time_last_digitUpdate_mode0 > time_btw_digitUpdate_mode0) {

        if (blinking == 0) {
          Serial.println("Blinking 1 timer 1");

          for (int i = 0; i < 25; i++) {
            M5.dis.drawpix(i, colors[1]);
          }
          blinking = 1 ;
        }
        else {
          Serial.println("Blinking 2 tim 1");

          DisplayColor(one, 2);
          blinking = 0;
        }
        time_last_digitUpdate_mode0 = time_milli;
      }
    }

    if (face_timer2) {

      timer2_set = false;
      time_left2 = 1;


      TIME_SHOWING = false;
      TIME_SETTING = false;

      if (time_milli - time_last_digitUpdate_mode0 > time_btw_digitUpdate_mode0) {

        if (blinking == 0) {
          
          Serial.println("Blinking 1 tim 1");
          M5.dis.clear();
          for (int i = 0; i < 25; i++) {
            M5.dis.drawpix(i, colors[2]);
          }
          blinking = 1 ;
        }
        else {
          Serial.println("Blinking 2 tim 2");
          DisplayColor(two, 2);
          blinking = 0;
        }
        time_last_digitUpdate_mode0 = time_milli;
      }
    }
    if (shaken()) {
      Serial.println("Shaken devide detected and entered the functio");
      TIME_BLINKING = false;
      TIME_SETTING = true;
    }
  }

  //Refresh chip in equal intervals
  if (time_milli - timeSinceLastChipRefresh > timeBtwChipRefresh) {

    M5.IMU.getAccelData(&accX, &accY, &accZ);

    timeSinceLastChipRefresh = time_milli;
  }
}

//--------------------------------------------------

bool shaken() {
  bool test = false;
  float magnitude_acc = 0;

  magnitude_acc = sqrt(accX * accX + accY * accY + accZ * accZ);

  if (magnitude_acc > acc_thold) {
    test = true;
    Serial.println("SHAKE DETECTED ----------------------");
  }
  return test;
}


int check_mode_switch() {

  unsigned long final_length_timer ;

  //  Serial.print("The magnitude of the X acceleration is: ");
  //  Serial.println(accX);

  if (((abs(accX) > 0.37) || (abs(accY) > 0.37)) || (abs(accX) > 0.37) && (abs(accY) > 0.37)) {


    if (time_milli - time_milli_last_press > time_btw_btn_press) {
      time_milli_last_press  = time_milli;

      if (accX > 0) {
        time_to_be_set --;
        DisplayColor(minus, 1);

        Serial.println("Tap from the right");
        Serial.println(len_timer1);
      }
      else {
        time_to_be_set ++;
        DisplayColor(plus, 2);
        Serial.println(len_timer1);
        Serial.println("Tap from the left");
      }

      for (int i = 0; i < time_to_be_set; i++)
      {
        M5.dis.drawpix(i, colors[3]);
      }
    }
  }
  return time_to_be_set;
}


void set_timer1(unsigned long & initial_t) {
  initial_t = time_milli;
  timer1_set = true;
}

void set_timer2(unsigned long &initial_t) {
  initial_t = time_milli;
  timer2_set = true;
}

bool set_timer() {
  bool check_timer = false;

  M5.update();

  if (M5.Btn.wasPressed()) {
    if (time_milli - timeSinceLastModeButtonPress > timeBtwLastModeButtonPress) {
      timeSinceLastModeButtonPress  = time_milli;
      check_timer = true;

      TIME_SETTING = false;
      TIME_SHOWING = true;

      Serial.println(initial_time1);
      Serial.println("timer 1 actived");
    }
  }
  return check_timer;
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
