//exemple given by prince

/*#include <M5Atom.h>



void setup() {
  Serial.begin(115200);

  M5.begin();
  M5.IMU.Init();
}


void loop() {
  float temp_value;

  M5.IMU.getTempData(&temp_value);

  Serial.print("temp: ");
  Serial.println(temp_value);
  delay(1000);
  
  
}*/

#include <M5StickC.h>

float temp = 0;



void setup() {
  M5.begin();
  M5.IMU.Init();
  
}



void loop() {
  
  M5.IMU.getTempData(&temp); //function getting temperature data 
  //M5.Lcd.setCursor(0, 0);
  //Serial.println("Temperature : %.2f C", temp); 
  delay(1000);


  
}
