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

int avr = 0 ;
int sum = 0 ;
for (int i = 0 ; i < 60000 ; i++ ){
  M5.IMU.getTempData(&temp);
  sum = sum + temp ;
}
avr = sum /60000 ;

Serial.println(avr);
if (avr <= 15)
{leds[24] = CRGB::Red;}
else if (avr > 15 && avr <=25){
leds[24] = CRGB::Red;
leds[23] = CRGB::Red;}
else if (avr >25 && avr <=35){
leds[24] = CRGB::Red;
leds[23] = CRGB::Red;
leds[22] = CRGB::Red;}
else if (avr >35 && avr <=45){
leds[24] = CRGB::Red;
leds[23] = CRGB::Red;
leds[22] = CRGB::Red;
leds[21] = CRGB::Red;}
else if (avr > 45){
leds[24] = CRGB::Red;
leds[23] = CRGB::Red;
leds[22] = CRGB::Red;
leds[21] = CRGB::Red;
leds[20] = CRGB::Red;}
FastLED.show();


for (int i = 0 ; i < 60000 ; i++ ){
  M5.IMU.getTempData(&temp);
  sum = sum + temp ;
}
avr = sum /60000 ;


Serial.println(avr);
if (avr <= 15)
{leds[19] = CRGB::Red;}
else if (avr > 15 && avr <=25){
leds[19] = CRGB::Red;
leds[18] = CRGB::Red;}
else if (avr >25 && avr <=35){
leds[19] = CRGB::Red;
leds[18] = CRGB::Red;
leds[17] = CRGB::Red;}
else if (avr >35 && avr <=45){
leds[19] = CRGB::Red;
leds[18] = CRGB::Red;
leds[17] = CRGB::Red;
leds[16] = CRGB::Red;}
else if (avr > 45){
leds[19] = CRGB::Red;
leds[18] = CRGB::Red;
leds[17] = CRGB::Red;
leds[16] = CRGB::Red;
leds[15] = CRGB::Red;}
FastLED.show();



for (int i = 0 ; i < 60000 ; i++ ){
  M5.IMU.getTempData(&temp);
  sum = sum + temp ;
}
avr = sum /60000 ;


Serial.println(avr);
if (avr <= 15)
{leds[14] = CRGB::Red;}
else if (avr > 15 && avr <=25){
leds[14] = CRGB::Red;
leds[13] = CRGB::Red;}
else if (avr >25 && avr <=35){
leds[14] = CRGB::Red;
leds[13] = CRGB::Red;
leds[12] = CRGB::Red;}
else if (avr >35 && avr <=45){
leds[14] = CRGB::Red;
leds[13] = CRGB::Red;
leds[12] = CRGB::Red;
leds[11] = CRGB::Red;}
else if (avr > 45){
leds[14] = CRGB::Red;
leds[13] = CRGB::Red;
leds[12] = CRGB::Red;
leds[11] = CRGB::Red;
leds[10] = CRGB::Red;}
FastLED.show();


for (int i = 0 ; i < 60000 ; i++ ){
  M5.IMU.getTempData(&temp);
  sum = sum + temp ;
}
avr = sum /60000 ;


Serial.println(avr);
if (avr <= 15)
{leds[9] = CRGB::Red;}
else if (avr > 15 && avr <=25){
leds[9] = CRGB::Red;
leds[8] = CRGB::Red;}
else if (avr >25 && avr <=35){
leds[9] = CRGB::Red;
leds[8] = CRGB::Red;
leds[7] = CRGB::Red;}
else if (avr >35 && avr <=45){
leds[9] = CRGB::Red;
leds[8] = CRGB::Red;
leds[7] = CRGB::Red;
leds[6] = CRGB::Red;}
else if (avr > 45){
leds[9] = CRGB::Red;
leds[8] = CRGB::Red;
leds[7] = CRGB::Red;
leds[6] = CRGB::Red;
leds[5] = CRGB::Red;}
FastLED.show();



for (int i = 0 ; i < 60000 ; i++ ){
  M5.IMU.getTempData(&temp);
  sum = sum + temp ;
}
avr = sum /60000 ;

Serial.println(avr);
if (avr <= 15)
{leds[4] = CRGB::Red;}
else if (avr > 15 && avr <=25){
leds[4] = CRGB::Red;
leds[3] = CRGB::Red;}
else if (avr >25 && avr <=35){
leds[4] = CRGB::Red;
leds[3] = CRGB::Red;
leds[2] = CRGB::Red;}
else if (avr >35 && avr <=45){
leds[4] = CRGB::Red;
leds[3] = CRGB::Red;
leds[2] = CRGB::Red;
leds[1] = CRGB::Red;}
else if (avr > 45){
leds[4] = CRGB::Red;
leds[3] = CRGB::Red;
leds[2] = CRGB::Red;
leds[1] = CRGB::Red;
leds[0] = CRGB::Red;}
FastLED.show();

  
M5.update();

}
