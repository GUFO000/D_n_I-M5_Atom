#include <M5Atom.h>

// the setup routine runs once when M5Stack starts up
void setup(){

  // Initialize the M5Stack object
  M5.begin(true,false,true);

  // LCD display
  //M5.Lcd.print("Hello World!");
  //M5.Lcd.print("M5Stack is running successfully!");
}
  CRGB colors[] = {
    0xff0000,
    0xff8000,
    0xffff00,
    0x80ff00,
    0x00ff00,
    0x00ff80,
    0x00ffff,
    0x0080ff,
    0x0000ff,
    0x8000ff,
    0xff00ff,
    0xff0080
  };
  //M5.dis.drawpix(0,0,0xffffff);
int ptr =0;


// the loop routine runs over and over again forever
void loop() {
  int x,y,p;
  p=ptr;
  for(x=0;x<5;x++){
    for(y=0;y<5;y++){
        M5.dis.drawpix(x,y,colors[p]);
        p= (p +1)%11;
      }
    }
  delay(100);

}
