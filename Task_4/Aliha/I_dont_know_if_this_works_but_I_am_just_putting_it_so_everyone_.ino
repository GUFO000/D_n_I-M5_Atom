[Some code I found online featuring some alterations I have made] I dont have the Atom so I dont exactly know how much this works.

#include <M5Atom.h>
#include <FastLED.H>

float accx, accy, accz;


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
 M5.IMU.getAccelData (&accx, &accy, &accz);
 {
  if (accx==0 && accy ==0 && accz ==0)
      Serial.println("Showing LEDs");
    for(int num=0; num<NUM_LEDS; num++) 
    {
    Serial.println(num);
    leds[num] = CRGB::Red;
    FastLED.show(); 
    delay(50);
    }
 }
}
