#include "M5Atom.h"  //not needed
#include <FastLED.h>

#define NUM_LEDS 25
#define DATA_PIN 27

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  delay(1000);

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
  
  delay(100);
 
  
  
    leds[0] = CRGB::Red;
    leds[1] = CRGB::Red;
    leds[2] = CRGB::Red;
    leds[3] = CRGB::Red;
    leds[4] = CRGB::Red;
    leds[5] = CRGB::Red;
    leds[6] = CRGB::Red;
    leds[7] = CRGB::Red;
    leds[8] = CRGB::Red;
    leds[9] = CRGB::Red;
    leds[10] = CRGB::Red;
    leds[11] = CRGB::Red;
    leds[12] = CRGB::Red;
    leds[13] = CRGB::Red;
    leds[14] = CRGB::Red;
    leds[15] = CRGB::Red;
    leds[16] = CRGB::Red;
    leds[17] = CRGB::Red;
    leds[18] = CRGB::Red;
    leds[19] = CRGB::Red;
    leds[20] = CRGB::Red;
    leds[21] = CRGB::Red;
    leds[22] = CRGB::Red;
    leds[23] = CRGB::Red;
    leds[24] = CRGB::Red;
    
  FastLED.show(); 

M5.update();

}
