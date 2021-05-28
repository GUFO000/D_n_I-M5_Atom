#include <M5Atom.h>

void setup(){

  M5.begin(true,false,true);

}

  CRGB colors[] = {
    0xfe0000,
    0x1ED35E
  };
  int mat,x,y;

void loop() {

  if(M5.Btn.wasPressed()) {
    mat = 1;
    for(x=0;x<5;x++){
      for(y=0;y<5;y++){
        M5.dis.drawpix(x,y,colors[mat]);
        }
      }
    }
    else {
      mat = 0;
      for(x=0;x<5;x++){
        for(y=0;y<5;y++){
          M5.dis.drawpix(x,y,colors[mat]);
          }
        }
      }

 
  delay(400);
  M5.update();
}
