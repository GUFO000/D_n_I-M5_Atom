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




/*#include <M5Atom.h>


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
  
   /*for(x=0;x<5;x++){
      for(y=0;y<5;y++){
          M5.dis.drawpix(x,y,0xffffff); //function to the whole color
       }
   }*/

   
   /*M5.dis.clear();
   for(int i=0;i<=25;i++){
   M5.dis.drawpix(i, 0xff0000);
    
   }
  
   */
   
   /*
    * for(x=0;x<5;x++){
      for(y=0;y<5;y++){
        M5.dis.drawpix(x,y,0xffffff); //function to the whole color
       }
   }
    //M5.dis.displaybuff(3);
    delay(1000);
  M5.dis.clear();
  delay(1000);
   
    
   oldX = x;
   oldY = y;
   
   
  }while ( accX != 0 && accY != 0 && oldX > 0);
  
   M5.update();
   
 
    
}*/







#include <M5Atom.h>
#include <FastLED.H>

float oldX , oldY ;

void setup(){

  M5.begin(true,false,true);
  M5.IMU.Init();
  Serial.begin(115200);
  oldX = -1;
  oldY = -1;
  Serial.println("");
  Serial.println("Initializing M5Stack Atom Matrix");
  
}

  CRGB colors[] = {
    0xfe0000,
    0x1ED35E
  };

int a, b ; 

void loop() {

  float accX, accY, accZ;
  int x, y;
  

  M5.IMU.getAccelData(&accX, &accY, &accZ); // the function to get acceleration data 
  x = constrain(accX * 5 + 3, 0, 4);
  y = constrain(accY * 5 + 3, 0, 4);
  
  if (accX<= 0.5 && accY<=0.5 && oldX <=0.5){
   for (a=0;a<5;a++)
   { for (b= 0 ; b < 5; b++)
   {M5.dis.drawpix (a,b, 0xff0000);
   }
   }
    
   
  delay(1000);
  M5.dis.clear();
  delay(1000);

  }

  else if (accX <=0.5 && accY<=0.5 && oldX>=0.5){
    for (a=0;a<5;a++)
  { for (b= 0 ; b < 5; b++)
  {M5.dis.drawpix (a,b, 0x0080ff);
  }
  }
    
  delay(1000);
  M5.dis.clear();
  delay(1000);
}
    
   oldX = accX;
   oldY = accY;
   
   M5.update();
   
}