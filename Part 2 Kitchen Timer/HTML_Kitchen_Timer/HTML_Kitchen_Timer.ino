#include "M5Atom.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

int n, mat;
char string_temp[10];
const char *ssid = "GROUP19";
const char *password = "123456789";
WiFiServer server(80);

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
void DisplayInvertedColor(int number[], int fillColor); 
void print_inverted_digit(char digit);



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

long web_len_timer1 = 20000; //120 000 is an exemple = start of the program
long web_len_timer2 = 10000;

int time_left1 = 1;
int time_left2 = 1;

char time_to_print[20];
int time_to_be_set = 0;

int blinking = 0;

//-----------------------------------------------------------------

void setup() {
  M5.begin(true, false, true);
  M5.IMU.Init();
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");


  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
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
        web_len_timer1 = time_to_be_set * 60;
        set_timer1(initial_time1) ;
        time_to_be_set = 0;
      }
    }

    if (face_timer2) {

      check_mode_switch();


      if (set_timer()) {
        len_timer2 = time_to_be_set * 60000;
        web_len_timer2 = time_to_be_set * 60;
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

        Serial.print("Time remaining for timer 1:");
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
   
        Serial.print("Time remaining for timer 2: ");
        Serial.println(time_to_print);
        
        if (n == strlen(time_to_print)) {
          n = 0;
          M5.dis.clear();
        }
        else {
          print_inverted_digit(time_to_print[n]);
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
          //Serial.println("Blinking 1 timer 1");

          for (int i = 0; i < 25; i++) {
            M5.dis.drawpix(i, colors[1]);
          }
          blinking = 1 ;
        }
        else {
          //Serial.println("Blinking 2 tim 1");

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
          
          //Serial.println("Blinking 1 tim 1");
          M5.dis.clear();
          for (int i = 0; i < 25; i++) {
            M5.dis.drawpix(i, colors[2]);
          }
          blinking = 1 ;
        }
        else {
          //Serial.println("Blinking 2 tim 2");
          DisplayColor(two, 2);
          blinking = 0;
        }
        time_last_digitUpdate_mode0 = time_milli;
      }
    }
    if (shaken()) {
      TIME_BLINKING = false;
      TIME_SETTING = true;
    }
  }

  //Refresh chip in equal intervals
  if (time_milli - timeSinceLastChipRefresh > timeBtwChipRefresh) {

    M5.IMU.getAccelData(&accX, &accY, &accZ);

    timeSinceLastChipRefresh = time_milli;
  }

  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        
        if (currentLine.endsWith("GET /T1")) {

          
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head>");
          client.println("<script type=\"text/javascript\">");
          //client.println ("var var2 = document.getElementById(\"t2value\")");
          client.println("window.onload = function() {");
          client.println("httpGetAsync(\"/value1\");");
          client.println("function httpGetAsync(theUrl) { ");
          client.println("var xmlHttp = new XMLHttpRequest();");
          client.println("var frequency_val = 1000;");
          client.println("xmlHttp.onreadystatechange = function() { ");
          client.println("if (xmlHttp.readyState == 4 && xmlHttp.status == 200)");
          client.println("document.getElementById(\"val\").innerHTML = xmlHttp.responseText; }");
          client.println("xmlHttp.open(\"GET\", theUrl, true); ");
          client.println("xmlHttp.send(null)");
          client.println("setTimeout(function(){httpGetAsync(\"/value1\")}, frequency_val); } }");
          client.println("</script>");
          client.println("</head>");
          client.println("<body>");
          client.print("<p style=\"font-size: 70px; font-style: arial; display: center; text-align:center; color:black\">TIMER 1</p> <br>");
          client.println("<h2 style=\"font-size: 64px; font-style: arial; display: center; text-align: center; color: gray\"> Time Left: </h2> ");
          client.println("<h2 id=\"val\" style=\"font-size: 64px; display: center; text-align : center; color:maroon\"> </h2> <br>");
          client.println("</body>");
          client.println("</html>"); 
        }
        if (currentLine.endsWith("GET /T2")) {
          
         
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head>");
          client.println("<script type=\"text/javascript\">");
          //client.println ("var var2 = document.getElementById(\"t2value\")");
          client.println("window.onload = function() {");
          client.println("httpGetAsync(\"/value2\");");
          client.println("function httpGetAsync(theUrl2) { ");
          client.println("var xmlHttp2 = new XMLHttpRequest();");
          client.println("var frequency_val = 1000;");
          client.println("xmlHttp2.onreadystatechange = function() { ");
          client.println("if (xmlHttp2.readyState == 4 && xmlHttp2.status == 200)");
          client.println("document.getElementById(\"val\").innerHTML = xmlHttp2.responseText; }");
          client.println("xmlHttp2.open(\"GET\", theUrl2, true); ");
          client.println("xmlHttp2.send(null)");
          client.println("setTimeout(function(){httpGetAsync(\"/value2\")}, frequency_val); } }");
          client.println("</script>");
          client.println("</head>");
          client.println("<body>");
          client.print("<p style=\"font-size: 70px; font-style: arial; display: center; text-align:center; color:black\">TIMER 2</p> <br>");
          client.println("<h2 style=\"font-size: 64px; font-style: arial; display: center; text-align: center; color: gray\"> Time Left: </h2> ");
          client.println("<h2 id=\"val\" style=\"font-size: 64px; display: center; text-align : center; color:maroon\"> </h2> <br>");
          client.println("</body>");
          client.println("</html>"); 
        
        }

        

        if (currentLine.endsWith("GET /value1")) {
         
          web_len_timer1--;
          client.println (web_len_timer1);
          
          
        }
      
      if (currentLine.endsWith("GET /value2")) {
         
          web_len_timer2--;
          client.println (web_len_timer2);
          
          
        }
        
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
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
      Serial.println("timer  actived");
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

void DisplayInvertedColor(int number[], int fillColor) {
  M5.dis.clear();
  for (int i = 0; i <25; i++)
  {
    if (number[24-i] == 1) {
      M5.dis.drawpix(i, colors[fillColor]);
    }
  }
}

void print_inverted_digit(char digit) {
  if (digit == '0') {
    DisplayInvertedColor(zero, 1);
  }
  else if (digit == '1') {
    DisplayInvertedColor(one, 1);
  }
  else if (digit == '2') {
    DisplayInvertedColor(two, 1);
  }
  else if (digit == '3') {
    DisplayInvertedColor(tre, 1);
  }
  else if (digit == '4') {
    DisplayInvertedColor(four, 1);
  }
  else if (digit == '5') {
    DisplayInvertedColor(five, 1);
  }
  else if (digit == '6') {
    DisplayInvertedColor(six, 1);
  }
  else if (digit == '7') {
    DisplayInvertedColor(seven, 1);
  }
  else if (digit == '8') {
    DisplayInvertedColor(eight, 1);
  }
  else if (digit == '9') {
    DisplayInvertedColor(nine, 1);
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
}
