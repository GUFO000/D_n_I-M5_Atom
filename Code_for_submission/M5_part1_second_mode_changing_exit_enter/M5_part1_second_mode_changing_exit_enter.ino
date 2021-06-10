#include "M5Atom.h"

int n, mat;
char string_temp[10];

bool flag = false;
int counter_graph  = 0;
int array_pos = 0;
int counter = 0;

float array_temp[5];
float temp_60_average = 0;


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

bool face_down();
bool face_up();
int check_mode_switch();
bool enter_exit_mode();
void DisplayColor(int number[], int fillColor);

void update_temp_average();

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
float ahrsX_pitch, ahrsY_roll, ahrsZ_yaw;
float temp, tempf;

//variables to identify LED on the matrix
int x, y;

//variable to select element from matrix of colors
int matrix_color = 0;

//Variable to keep track of the active mode
int active_mode = 0;

//int to store result of checking if mode was changed (funtion does not run twice)
int store_mode =  0;

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

unsigned long timeSinceLastDigitOnScreen;
unsigned long timeBtwDigitsOnScreen = 100;

unsigned long timeSinceLastModeButtonPress = 0;
unsigned long timeBtwLastModeButtonPress = 100;
unsigned long time_milli_lastButtonPress = 0;

unsigned long time_btw_digitUpdate_mode0 = 600;
unsigned long time_last_digitUpdate_mode0 = 0;


bool MODE_DETECTING = false;
bool MODE_SET = false;

float temp_average = 0;
float temp_number_entries = 0;

//-----------------------------------------------------------------

void setup() {
  M5.begin(true, false, true);
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
        n = 0;
        dtostrf(temp, 5, 2, string_temp);
        break;

      //Show average of last 24 hours of temperature + Units
      case 1:
        DisplayColor(one, 1);
        n = 0;
        dtostrf(temp_average, 5, 2, string_temp);
        break;

      //Show color scale of temperature range + current temperature as color
      case 2:
        DisplayColor(two, 1);
        break;

      //Show graph of temperature across a predefined range
      case 3:
        DisplayColor(tre, 1);
        for (int i = 0; i < 5; i++) {
          array_temp[i] = temp_average;
        }
        counter  = 0;
        array_pos = 0;
        temp_60_average = 0;
        break;

      //Change units
      case 4:
        DisplayColor(four, 1);
        break;
    }

    if (enter_exit_mode()) {
      MODE_DETECTING = false;
      MODE_SET = true;
    }
  }

  //in this if we will execute the different modes
  if (face_is_up && MODE_SET) {
    switch (active_mode) {
      case 0:
        dtostrf(temp, 5, 2, string_temp);
        /*//        if (time_milli - time_last_update_mode0 > time_btw_update_mode0) {
          //          string_temp[10] = ' ';
          //          Serial.print(temp);
          //
          //          dtostrf(temp, 5, 2, string_temp);
          //          Serial.print("string tmp---------");
          //          Serial.println(string_temp);
          //          time_last_update_mode0 = time_milli;
          //        }*/

        if (time_milli - time_last_digitUpdate_mode0 > time_btw_digitUpdate_mode0) {
          Serial.print("---------string tmp");
          Serial.println(string_temp);
          if (n == strlen(string_temp)) {
            n = 0;
            DisplayColor(letter_c, 1);
          }
          else {
            print_digit(string_temp[n]);
            n++;
          }
          time_last_digitUpdate_mode0 = time_milli;
        }
        break;
      case 1:
        //DisplayColor(one, 2);
        dtostrf(temp_average, 5, 2, string_temp);
        if (time_milli - time_last_digitUpdate_mode0 > time_btw_digitUpdate_mode0) {

          if (n == strlen(string_temp)) {
            n = 0;
            DisplayColor(letter_c, 1);
          }
          else {
            print_digit(string_temp[n]);
            n++;
          }
          time_last_digitUpdate_mode0 = time_milli;
        }
        break;
      case 2:
        M5.dis.clear();
        M5.dis.drawpix(0, 4, colors[3] );
        M5.dis.drawpix(1, 4, colors[4] );
        M5.dis.drawpix(2, 4, colors[5] );
        M5.dis.drawpix(3, 4, colors[6] );
        M5.dis.drawpix(4, 4, colors[7] );

        if (temp > 40) {
          mat  = 7;
        }
        else if (temp > 35) {
          mat  = 6;
        }
        else if (temp > 30) {
          mat  = 5;
        }
        else if (temp > 25) {
          mat  = 4;
        }
        else if (temp > 20) {
          mat  = 3;
        }

        for (x = 0; x < 5; x++) {
          for (y = 0; y < 3; y++) {
            M5.dis.drawpix(x, y, colors[mat]);
          }
        }
        break;


      case 3:
        flag = true;
        M5.dis.clear();
        for (int i = 0; i < 5; i++) {
          Serial.print(i);
          Serial.print(" ");
          Serial.println(array_temp[i]);
        }
        for (int i = 0; i < 5; i++) {
          if (array_temp[i] > 45) {
            M5.dis.drawpix(i, 0, colors[7]);
          }
          else if (array_temp[i] > 40) {
            M5.dis.drawpix(i, 1, colors[6]);
          }
          else if (array_temp[i] > 35) {
            M5.dis.drawpix(i, 2, colors[5]);
          }
          else if (array_temp[i] > 30) {
            M5.dis.drawpix(i, 3, colors[4]);
          }
          else { /*if(array_temp[i]> 25)*/
            M5.dis.drawpix(i, 4, colors[3]);
          }
        }
        break;


      case 4:
        tempf = (temp * (9 / 5)) + 32;
        dtostrf(tempf, 5, 2, string_temp);
        Serial.println(tempf);
        if (time_milli - time_last_digitUpdate_mode0 > time_btw_digitUpdate_mode0) {
          if (n == strlen(string_temp)) {
            n = 0;
            DisplayColor(letter_f, 1);
          }
          else {
            print_digit(string_temp[n]);
            n++;
          }
          time_last_digitUpdate_mode0 = time_milli;
        }
        break;
    }
    if (enter_exit_mode()) {
      MODE_DETECTING = true;
      MODE_SET = false;
    }
  }

  //Refresh chip in equal intervals
  if (time_milli - timeSinceLastChipRefresh > timeBtwChipRefresh) {

    M5.IMU.getTempData(&temp);
    update_temp_average();

    if (flag) {
      Serial.print("Counter  ");
      Serial.print(counter);
      Serial.print(" array pos  ");
      Serial.println(array_pos);
      if (counter == 500){
        array_temp[array_pos]  = temp_60_average/500;
        temp_60_average = 0;
        array_pos = (array_pos + 1)%5;
        counter = 0;
      }
      else {
        temp_60_average = temp_60_average + temp;
        Serial.print(" temp_60_average  ");
        Serial.println(temp_60_average);
        counter++;
      }
    }

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

bool enter_exit_mode() {
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

void update_temp_average() {
  temp_number_entries++;
  temp_average = (temp_number_entries - 1) / temp_number_entries * temp_average + temp / temp_number_entries;

}



void print_digit(char digit) {
  if (digit == '0') {
    DisplayColor(zero, 2);
  }
  else if (digit == '1') {
    DisplayColor(one, 2);
  }
  else if (digit == '2') {
    DisplayColor(two, 2);
  }
  else if (digit == '3') {
    DisplayColor(tre, 2);
  }
  else if (digit == '4') {
    DisplayColor(four, 2);
  }
  else if (digit == '5') {
    DisplayColor(five, 2);
  }
  else if (digit == '6') {
    DisplayColor(six, 2);
  }
  else if (digit == '7') {
    DisplayColor(seven, 2);
  }
  else if (digit == '8') {
    DisplayColor(eight, 2);
  }
  else if (digit == '9') {
    DisplayColor(nine, 2);
  }
  else if (digit == '.') {
    M5.dis.clear();
    M5.dis.drawpix(22, colors[2] );
  }
}
