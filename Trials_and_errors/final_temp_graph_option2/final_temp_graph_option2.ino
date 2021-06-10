
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
int avr ;
int sum  ;


for (int j = 0 ; j < 25; j++){
  //updating the time for each led
 temp = 0;
 sum = 0 ;
 avr = 0 ;

//calculating the average for each minute of each led
 for (int i = 0 ; i < 60000 ; i++ ){
  M5.IMU.getTempData(&temp);
  sum = sum + temp ;
}
avr = sum /60000 ;

// assigning a color to each led depending on the range  
Serial.println(avr);
if (avr <= 15)
{leds[j] = CRGB::Blue;}
else if (avr > 15 && avr <=25){
leds[j] = CRGB::Green;}
else if (avr >25 && avr <=35){
leds[j] = CRGB::Yellow;}
else if (avr >35 && avr <=45){
leds[j] = CRGB::White;}
else if (avr > 45){
leds[j] = CRGB::Red;}
FastLED.show();

}
M5.update();

}
