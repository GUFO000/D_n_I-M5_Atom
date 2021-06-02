#include "M5Atom.h"  //not needed
#include <FastLED.h>

#define NUM_LEDS 25
#define DATA_PIN 27
int n;

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  delay(1000);
   M5.IMU.Init();

  Serial.println("");
  Serial.println("Initializing M5Stack Atom Matrix");
 

  
  Serial.println("\nInitializing FastLED");
 
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);

  
  Serial.println("Setting brightness");
  FastLED.setBrightness(20);
  Serial.println("Finishing setup");
}

void loop() {

float temp;
 M5.IMU.getTempData(&temp);
  Serial.println(temp);

char buffer[10]; 
    dtostrf(temp, 5, 2, buffer);  

    
for(int n = 0; n < strlen(buffer); n++) 

{
  Serial.println(buffer[n]);
 delay (100);

 if ( buffer [n] == '1')
{   leds[10] = CRGB::White;
    leds[11] = CRGB::White;
    leds[12] = CRGB::White;
    leds[13] = CRGB::White;
    leds[14] = CRGB::White;
    FastLED.show();
}

else if ( buffer [n] == '2')
{   leds[0] = CRGB::White;
    leds[1] = CRGB::White;
    leds[2] = CRGB::White;
    leds[4] = CRGB::White;
    leds[5] = CRGB::White;
    leds[7] = CRGB::White;
    leds[9] = CRGB::White;
    leds[10] = CRGB::White;
    leds[12] = CRGB::White;
    leds[14] = CRGB::White;
    leds[15] = CRGB::White;
    leds[17] = CRGB::White;
    leds[19] = CRGB::White;
    leds[20] = CRGB::White;
    leds[22] = CRGB::White;
    leds[23] = CRGB::White;
    leds[24] = CRGB::White;
    FastLED.show();
}

else if (buffer [n] == '3')
{   leds[0] = CRGB::White;
    leds[1] = CRGB::White;
    leds[2] = CRGB::White;
    leds[3] = CRGB::White;
    leds[4] = CRGB::White;
    leds[5] = CRGB::White;
    leds[7] = CRGB::White;
    leds[9] = CRGB::White;
    leds[10] = CRGB::White;
    leds[12] = CRGB::White;
    leds[14] = CRGB::White;
    leds[15] = CRGB::White;
    leds[17] = CRGB::White;
    leds[19] = CRGB::White;
    leds[20] = CRGB::White;
    leds[22] = CRGB::White;
    leds[24] = CRGB::White;
    FastLED.show();
}

else if (buffer [n] == '4')
{   leds[0] = CRGB::White;
    leds[1] = CRGB::White;
    leds[2] = CRGB::White;
    leds[3] = CRGB::White;
    leds[4] = CRGB::White;
    leds[7] = CRGB::White;
    leds[12] = CRGB::White;
    leds[17] = CRGB::White;
    leds[20] = CRGB::White;
    leds[21] = CRGB::White;
    leds[22] = CRGB::White;
    FastLED.show();
}

else if ( buffer [n]== '5')
{

 leds[0] = CRGB::White;
    leds[2] = CRGB::White;
    leds[3] = CRGB::White;
    leds[4] = CRGB::White;
    leds[5] = CRGB::White;
    leds[7] = CRGB::White;
    leds[9] = CRGB::White;
    leds[10] = CRGB::White;
    leds[12] = CRGB::White;
    leds[14] = CRGB::White;
    leds[15] = CRGB::White;
    leds[17] = CRGB::White;
    leds[19] = CRGB::White;
    leds[20] = CRGB::White;
    leds[21] = CRGB::White;
    leds[22] = CRGB::White;
    leds[24] = CRGB::White;
    FastLED.show();
    
    
}

else if (buffer [n]== '6')
{
    leds[0] = CRGB::White;
    leds[2] = CRGB::White;
    leds[3] = CRGB::White;
    leds[4] = CRGB::White;
    leds[5] = CRGB::White;
    leds[7] = CRGB::White;
    leds[9] = CRGB::White;
    leds[10] = CRGB::White;
    leds[12] = CRGB::White;
    leds[14] = CRGB::White;
    leds[15] = CRGB::White;
    leds[17] = CRGB::White;
    leds[19] = CRGB::White;
    leds[20] = CRGB::White;
    leds[21] = CRGB::White;
    leds[22] = CRGB::White;
    leds[23] = CRGB::White;
    leds[24] = CRGB::White;
    FastLED.show();
    
}

else if (buffer [n]== '7')
{
    leds[0] = CRGB::White;
    leds[1] = CRGB::White;
    leds[2] = CRGB::White;
    leds[3] = CRGB::White;
    leds[4] = CRGB::White;
    leds[5] = CRGB::White;
    leds[10] = CRGB::White;
    leds[15] = CRGB::White;
    leds[20] = CRGB::White;
    FastLED.show();
    
}

else if (buffer [n]== '8')
{
    leds[0] = CRGB::White;
    leds[1] = CRGB::White;
    leds[2] = CRGB::White;
    leds[3] = CRGB::White;
    leds[4] = CRGB::White;
    leds[5] = CRGB::White;
    leds[7] = CRGB::White;
    leds[9] = CRGB::White;
    leds[10] = CRGB::White;
    leds[12] = CRGB::White;
    leds[14] = CRGB::White;
    leds[15] = CRGB::White;
    leds[17] = CRGB::White;
    leds[19] = CRGB::White;
    leds[20] = CRGB::White;
    leds[21] = CRGB::White;
    leds[22] = CRGB::White;
    leds[23] = CRGB::White;
    leds[24] = CRGB::White;
    FastLED.show();
    
}

else if (buffer [n]== '9')
{
    leds[0] = CRGB::White;
    leds[1] = CRGB::White;
    leds[2] = CRGB::White;
    leds[3] = CRGB::White;
    leds[4] = CRGB::White;
    leds[5] = CRGB::White;
    leds[7] = CRGB::White;
    leds[9] = CRGB::White;
    leds[10] = CRGB::White;
    leds[12] = CRGB::White;
    leds[14] = CRGB::White;
    leds[15] = CRGB::White;
    leds[17] = CRGB::White;
    leds[19] = CRGB::White;
    leds[20] = CRGB::White;
    leds[21] = CRGB::White;
    leds[22] = CRGB::White;
    leds[24] = CRGB::White;
    FastLED.show();
    
}

else if (buffer [n] == '0')
{
    leds[0] = CRGB::White;
    leds[1] = CRGB::White;
    leds[2] = CRGB::White;
    leds[3] = CRGB::White;
    leds[4] = CRGB::White;
    leds[5] = CRGB::White;
    leds[9] = CRGB::White;
    leds[10] = CRGB::White;
    leds[14] = CRGB::White;
    leds[15] = CRGB::White;
    leds[19] = CRGB::White;
    leds[20] = CRGB::White;
    leds[21] = CRGB::White;
    leds[22] = CRGB::White;
    leds[23] = CRGB::White;
    leds[24] = CRGB::White;
    FastLED.show();
    
}

else if (n == 2)
  { leds[14] = CRGB::White;
 FastLED.show(); }

 delay (500);
    leds[0] = CRGB::Black;
    leds[1] = CRGB::Black;
    leds[2] = CRGB::Black;
    leds[3] = CRGB::Black;
    leds[4] = CRGB::Black;
    leds[5] = CRGB::Black;
    leds[6] = CRGB::Black;
    leds[7] = CRGB::Black;
    leds[8] = CRGB::Black;
    leds[9] = CRGB::Black;
    leds[10] = CRGB::Black;
    leds[11] = CRGB::Black;
    leds[12] = CRGB::Black;
    leds[13] = CRGB::Black;
    leds[14] = CRGB::Black;
    leds[15] = CRGB::Black;
    leds[16] = CRGB::Black;
    leds[17] = CRGB::Black;
    leds[18] = CRGB::Black;
    leds[19] = CRGB::Black;
    leds [20] = CRGB::Black;
    leds[21] = CRGB::Black;
    leds[22] = CRGB::Black;
    leds[23] = CRGB::Black;
    leds[24] = CRGB::Black;
    FastLED.show();
 delay (500);
 
}
leds[10] = CRGB::White;
 FastLED.show();
 delay (500);
 leds[0] = CRGB::Black;
    leds[1] = CRGB::Black;
    leds[2] = CRGB::Black;
    leds[3] = CRGB::Black;
    leds[4] = CRGB::Black;
    leds[5] = CRGB::Black;
    leds[6] = CRGB::Black;
    leds[7] = CRGB::Black;
    leds[8] = CRGB::Black;
    leds[9] = CRGB::Black;
    leds[10] = CRGB::Black;
    leds[11] = CRGB::Black;
    leds[12] = CRGB::Black;
    leds[13] = CRGB::Black;
    leds[14] = CRGB::Black;
    leds[15] = CRGB::Black;
    leds[16] = CRGB::Black;
    leds[17] = CRGB::Black;
    leds[18] = CRGB::Black;
    leds[19] = CRGB::Black;
    leds [20] = CRGB::Black;
    leds[21] = CRGB::Black;
    leds[22] = CRGB::Black;
    leds[23] = CRGB::Black;
    leds[24] = CRGB::Black;
  delay (500);
    leds[0] = CRGB::White;
    leds[4] = CRGB::White;
    leds[5] = CRGB::White;
    leds[9] = CRGB::White;
    leds[10] = CRGB::White;
    leds[14] = CRGB::White;
    leds[15] = CRGB::White;
    leds[19] = CRGB::White;
    leds[20] = CRGB::White;
    leds[21] = CRGB::White;
    leds[22] = CRGB::White;
    leds[23] = CRGB::White;
    leds[24] = CRGB::White;
    FastLED.show();
 delay (500);
   leds[0] = CRGB::Black;
    leds[1] = CRGB::Black;
    leds[2] = CRGB::Black;
    leds[3] = CRGB::Black;
    leds[4] = CRGB::Black;
    leds[5] = CRGB::Black;
    leds[6] = CRGB::Black;
    leds[7] = CRGB::Black;
    leds[8] = CRGB::Black;
    leds[9] = CRGB::Black;
    leds[10] = CRGB::Black;
    leds[11] = CRGB::Black;
    leds[12] = CRGB::Black;
    leds[13] = CRGB::Black;
    leds[14] = CRGB::Black;
    leds[15] = CRGB::Black;
    leds[16] = CRGB::Black;
    leds[17] = CRGB::Black;
    leds[18] = CRGB::Black;
    leds[19] = CRGB::Black;
    leds [20] = CRGB::Black;
    leds[21] = CRGB::Black;
    leds[22] = CRGB::Black;
    leds[23] = CRGB::Black;
    leds[24] = CRGB::Black;
    FastLED.show();
    delay (500);
M5.update();
delay (500);
}
