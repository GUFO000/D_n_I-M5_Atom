
#include "M5Atom.h"
int switch1 = 12;     // the number of the switch pin
int led1 =  4;      // the number of the LED pin

int prevState = LOW;
int currState;


void setup() 
 {
  // initialize the LED pin as an output:
  pinMode(led1, OUTPUT); 

                             
                             // initialize the switch pin as an input:
  pinMode(switch1, INPUT);     
 }

void loop()
 {

  currState = digitalRead(switch1);

  
  if (currState != prevState)
   {     
   digitalWrite(led1, HIGH);
   delay(100);
   digitalWrite(led1, LOW);
   delay(100);
  
    
   }
  prevState = currState;


  

 }
