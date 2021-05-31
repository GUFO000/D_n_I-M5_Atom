/*#include <M5Atom.h>

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
        M5.dis.drawpix(x,y,colors[mat]); //function to the whole color 
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
}*/




#include <M5Atom.h>


int oldX , oldY ;

void setup(){

  M5.begin(true,false,true);
  M5.IMU.Init();
  oldX = -1 ;
  oldY = -1;
}

  CRGB colors[] = {
    0xfe0000,
    0x1ED35E
  };
  

void loop() {

  float accX, accY, accZ;
  int x, y;
  

  M5.IMU.getAccelData(&accX, &accY, &accZ); // the function to get acceleration data 

  do{
  
   for(x=0;x<5;x++){
      for(y=0;y<5;y++){
          M5.dis.drawpix(x,y,0xffffff); //function to the whole color
       }
   }
   oldX = x;
   oldY = y;
   delay(10000000);
   M5.update();
  }while ( accX != 2 && accY != 2 );
  /* for(x=0;x<5;x++){
      for(y=0;y<5;y++){
          M5.dis.drawpix(x,y,0); //function to the whole color 
       }
  }
   
   delay (1000);
 */   
    
}
