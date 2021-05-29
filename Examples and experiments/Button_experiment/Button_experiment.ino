#include <M5Atom.h>

void setup(){

  M5.begin(true,false,true);

}

  CRGB colors[] = {
    0xfe0000,
    0x1ED35E
  };
  int p,x,y;

void loop() {

  if(M5.Btn.wasPressed()) {
    p = 1;
    for(x=0;x<5;x++){
      for(y=0;y<5;y++){
        M5.dis.drawpix(x,y,colors[p]);
        }
      }
    delay(100);
    }
    else {
      p = 0;
      for(x=0;x<5;x++){
        for(y=0;y<5;y++){
          M5.dis.drawpix(x,y,colors[p]);
          }
        }
      delay(100);
      }

 
  delay(300);
  M5.update();
}
