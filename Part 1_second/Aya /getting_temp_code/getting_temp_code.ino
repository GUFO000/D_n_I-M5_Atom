//exemple given by prince

/*#include <M5Atom.h>



void setup() {
  Serial.begin(115200);

  M5.begin();
  M5.IMU.Init();
}


void loop() {
  float temp_value;

  M5.IMU.getTempData(&temp_value);

  Serial.print("temp: ");
  Serial.println(temp_value);
  delay(1000);
  
  
}*/

#include <M5StickC.h>
#include <Adafruit_GFX.h>
 #include <Adafruit_NeoMatrix.h>
 #include <Adafruit_NeoPixel.h>

float temp = 0;

#define PIN 27


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PIN,
   NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
   NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
   NEO_GRB            + NEO_KHZ800);
 
const uint16_t colors[] = {
   matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };


void setup() {
  M5.begin();
  M5.IMU.Init();
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
}

int x    = matrix.width();
int pass = 0;

void loop() {
  
  M5.IMU.getTempData(&temp); //function getting temperature data 
  //M5.Lcd.setCursor(0, 0);
  //Serial.println("Temperature : %.2f C", temp); 
  delay(1000);


  //code to display the temperature
  
   matrix.fillScreen(0);
   matrix.setCursor(x, 0);
   matrix.print(F(temp));
   if(--x < -96) {
     x = matrix.width();
     if(++pass >= 3) pass = 0;
     matrix.setTextColor(colors[pass]);
   }
   matrix.show();
   delay(80);
   M5.update();
  
}
