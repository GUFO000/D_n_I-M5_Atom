
 #include <M5Atom.h>
 #include <Adafruit_GFX.h>
 #include <Adafruit_NeoMatrix.h>
 #include <Adafruit_NeoPixel.h>

 #define PIN 27
 
 

 
 Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PIN,
   NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
   NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
   NEO_GRB            + NEO_KHZ800);

 const uint16_t colors[] = {
   matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };
int x    = matrix.width();
 int pass = 0;
 float temp;
 int a,b;
 
 
 void setup() {
   M5.begin();
   M5.IMU.Init();
   matrix.begin();
   matrix.setTextWrap(false);
   matrix.setBrightness(20);
   matrix.setTextColor(colors[0]);
   
   matrix.fillScreen(0);
   matrix.setCursor(x, 0);
   matrix.print("Low");
   if(--x < -96) {
     x = matrix.width();
     if(++pass >= 3) pass = 0;
     matrix.setTextColor(colors[pass]);}
   
   matrix.show();
   delay (100);
   for (a=0;a<5;a++)
  { for (b = 0 ; b < 5;b++)
  {M5.dis.drawpix (a,b, 0xff0080);
  }
  }
  delay (200);
  matrix.fillScreen(0);
   matrix.setCursor(x, 0);
   matrix.print("Normal");
   if(--x < -96) {
     x = matrix.width();
     if(++pass >= 3) pass = 0;
     matrix.setTextColor(colors[pass]);}
   matrix.show();
   delay (100);
   for (a=0;a<5;a++)
  { for (b = 0 ; b < 5;b++)
  {M5.dis.drawpix (a,b, 0xff0000);
  }
  }
  delay (200);
  matrix.fillScreen(0);
   matrix.setCursor(x, 0);
   matrix.print("Normal");
   if(--x < -96) {
     x = matrix.width();
     if(++pass >= 3) pass = 0;
     matrix.setTextColor(colors[pass]);}
   matrix.show();
   delay (100);
   for (a=0;a<5;a++)
  { for (b = 0 ; b < 5;b++)
  {M5.dis.drawpix (a,b, 0xff0000);
  }
  }
  delay (200);
   matrix.fillScreen(0);
   matrix.setCursor(x, 0);
   matrix.print("High");
   if(--x < -96) {
     x = matrix.width();
     if(++pass >= 3) pass = 0;
     matrix.setTextColor(colors[pass]);}
   matrix.show();
   delay (100);
   for (a=0;a<5;a++)
  { for (b = 0 ; b < 5;b++)
  {M5.dis.drawpix (a,b, 0x00ff00);
  }
  }
   matrix.fillScreen(0);
   matrix.setCursor(x, 0);
   matrix.print("Very High");
   if(--x < -96) {
     x = matrix.width();
     if(++pass >= 3) pass = 0;
     matrix.setTextColor(colors[pass]);}
   matrix.show();
   for (a=0;a<5;a++)
  { for (b = 0 ; b < 5;b++)
  {M5.dis.drawpix (a,b, 0xff0000);
  }
  }
 }
 

 void loop() {

  matrix.fillScreen(0);
   matrix.setCursor(x, 0);
   matrix.print("CURRENT TEMPERATURE");
   if(--x < -96) {
     x = matrix.width();
     if(++pass >= 3) pass = 0;
     matrix.setTextColor(colors[pass]);}
   matrix.show();
  delay (100);
  M5.IMU.getTempData(&temp);
  Serial.println(temp);

  if (temp <=15)
   { for (a=0;a<5;a++)
  { for (b = 0 ; b < 5;b++)
  {M5.dis.drawpix (a,b, 0xff0080);
  }
  }
   }

  if (temp > 15 && temp <=30 )
   { for (a=0;a<5;a++)
  { for (b = 0 ; b < 5;b++)
  {M5.dis.drawpix (a,b, 0xff0000);
  }
  }
   }

 if (temp > 15 && temp <=30 )
   { for (a=0;a<5;a++)
  { for (b = 0 ; b < 5;b++)
  {M5.dis.drawpix (a,b, 0xff0000);
  }
  }
   }

 if (temp > 30 && temp <=35 )
   { for (a=0;a<5;a++)
  { for (b = 0 ; b < 5;b++)
  {M5.dis.drawpix (a,b, 0x00ff00);
  }
  }
   }

 
 if (temp > 35 )
   { for (a=0;a<5;a++)
  { for (b = 0 ; b < 5;b++)
  {M5.dis.drawpix (a,b, 0xff0000);
  }
  }
   }
 
delay(500);
M5.update();

  

  
  
   //matrix.fillScreen(0);
  // matrix.setCursor(x, 0);
   //matrix.print(temp);
   //if(--x < -96) {
    // x = matrix.width();
     //if(++pass >= 3) pass = 0;
     //matrix.setTextColor(colors[pass]);
   }
