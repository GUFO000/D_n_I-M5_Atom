#include "M5Atom.h"  
#include <FastLED.h>

#define NUM_LEDS 25
#define DATA_PIN 27


CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  delay(1000);
  
   M5.IMU.Init ();
   

  Serial.println("");
  Serial.println("Initializing M5Stack Atom Matrix");
  //M5.begin(true, false, true);  //not needed

  // Initialize the FastLED library for this device's configuration
  Serial.println("\nInitializing FastLED");
  //FastLED.addLeds<WS2812, DATA_PIN>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);

  // M5Stack recommends not setting this value greater than 20
  // to avoid melting the screen/cover over the LEDs
  Serial.println("Setting brightness");
  FastLED.setBrightness(20);
  Serial.println("Finishing setup");
}

void loop() {

float temp;

M5.IMU.getTempData(&temp);
Serial.println(temp);
if (temp <= 15)
{leds[0] = CRGB::Red;}
else if (temp > 15 && temp >=25)
{leds[1] = CRGB::Red;}
else if (temp >25 && temp >=35)
{leds[2] = CRGB::Red;}
else if (temp >35 && temp <=45)
{leds[3] = CRGB::Red;}
else if (temp > 45)
{leds[4] = CRGB::Red;}
FastLED.show();
  
 M5.IMU.getTempData(&temp);
Serial.println(temp);
if (temp <= 15)
{leds[5] = CRGB::Red;}
else if (temp > 15 && temp >=25)
{leds[6] = CRGB::Red;}
else if (temp >25 && temp >=35)
{leds[7] = CRGB::Red;}
else if (temp >35 && temp <=45)
{leds[8] = CRGB::Red;}
else if (temp > 45)
{leds[9] = CRGB::Red;}

FastLED.show();
   
M5.IMU.getTempData(&temp);
Serial.println(temp);
if (temp <= 15)
{leds[10] = CRGB::Red;}
else if (temp > 15 && temp >=25)
{leds[11] = CRGB::Red;}
else if (temp >25 && temp >=35)
{leds[12] = CRGB::Red;}
else if (temp >35 && temp <=45)
{leds[13] = CRGB::Red;}
else if (temp > 45)
{leds[14] = CRGB::Red;}  
FastLED.show();


    

M5.IMU.getTempData(&temp);
Serial.println(temp);
if (temp <= 15)
{leds[15] = CRGB::Red;}
else if (temp > 15 && temp >=25)
{leds[16] = CRGB::Red;}
else if (temp >25 && temp >=35)
{leds[17] = CRGB::Red;}
else if (temp >35 && temp <=45)
{leds[18] = CRGB::Red;}
else if (temp > 45)
{leds[19] = CRGB::Red;}

FastLED.show();

M5.IMU.getTempData(&temp);
Serial.println(temp);
if (temp <= 15)
{leds[20] = CRGB::Red;}
else if (temp > 15 && temp >=25)
{leds[21] = CRGB::Red;}
else if (temp >25 && temp >=35)
{leds[22] = CRGB::Red;}
else if (temp >35 && temp <=45)
{leds[23] = CRGB::Red;}
else if (temp > 45)
{leds[24] = CRGB::Red;}



FastLED.show();
  

  
  
    
  
M5.update();

}
