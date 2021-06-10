#include <M5Atom.h>

 int a,b;

 void setup() {
   M5.begin(true, true, true);
   Serial.begin(115200);
 }


 float temp;

 void loop() {
  
  M5.IMU.getTempData(&temp);
  Serial.println(temp);
//temp = 50;

 if (temp <=15){ // <= 15
    for (a=0;a<5;a++)
    {
      for (b = 0 ; b < 5;b++) {
        M5.dis.drawpix(a,b, 0xff0080);
      }
    }
  }
  else if (temp > 15 && temp <=30 ) // 15 < temp <= 30
   {
     for (a=0;a<5;a++)
     {
       for (b = 0 ; b < 5;b++)
       {
         M5.dis.drawpix (a,b,0x1ED35E );
       }
     }
   }
   else if (temp > 30 && temp <= 45 ) // 30 < temp <= 45
   {
     for (a=0;a<5;a++)
     {
       for (b = 0 ; b < 5;b++)
       {
         M5.dis.drawpix (a,b,0x00ff00  );
       }
     }
   }
   else if (temp > 45 ) // temp > 45
   {
     for (a=0;a<5;a++)
     {
       for (b = 0 ; b < 5;b++)
       {
         M5.dis.drawpix (a,b, 0xff0000 );
       }
     }
   }
   delay(100);
 M5.update();
 }
