#include <M5Atom.h>

char*messages [] = {
         "My name is Erica",
         "Professor is the best",
         "I like cheese",
         "My cat distracts me from work"
};



void setup() 
{
Serial.begin (9600);
}

void loop() 
{
int delayPeriod = random(2000,8000);
delay (delayPeriod);
int messageIndex = random(4);
Serial.println (messages[messageIndex]);

}
