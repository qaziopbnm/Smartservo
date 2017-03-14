#include <SoftwareSerial.h>
#include "MeAuriga.h"

MeSmartServo mysmartservo(PORT5);   //UART2 is on port 5
MePS2 MePS2(PORT_16);

long loopRun = 0, loopTime = 0;
short int cout = 500;
float j, f, k;
int t = 1,Speed = 255,sttep = 0;

void setup() {
  Serial.begin(115200);
  mysmartservo.begin(115200);
  MePS2.begin(115200);
  delay(5);
  mysmartservo.assignDevIdRequest();
  delay(50);
  Serial.println("setup!");
  loopTime = millis();
}
void RGB_Loop(){
  uint8_t red  = 150 * (1 + sin(t / 2.0 + j / 4.0) );
    uint8_t green = 150 * (1 + sin(t / 1.0 + f / 9.0 + 2.1) );
    uint8_t blue = 150 * (1 + sin(t / 3.0 + k / 14.0 + 4.2) );
    mysmartservo.setRGBLed(t, red, green, blue);
  j += random(1, 6) / 6.0;
  f += random(1, 6) / 6.0;
  k += random(1, 6) / 6.0;
}
void loop() { 
  MePS2.loop();
  mysmartservo.setPwmMove(1,sttep);
  if (MePS2.ButtonPressed(MeJOYSTICK_UP))
  {
    sttep = -Speed;
    Serial.println("UP is pressed!");
  }
  if (MePS2.ButtonPressed(MeJOYSTICK_DOWN))
  {
    sttep = Speed;
    Serial.println("DOWN is pressed!");
  }
   if (MePS2.ButtonPressed(MeJOYSTICK_LEFT))
  {
    sttep = 0;
    Serial.println("LEFT is pressed!");
  }
  if (MePS2.ButtonPressed(MeJOYSTICK_L1))
  {
    Speed = 255;
    Serial.println("L1 is pressed!");
  }
  if (MePS2.ButtonPressed(MeJOYSTICK_L2))
  {
    Speed = 80;
    Serial.println("L2 is pressed!");
    
  }
  if (MePS2.ButtonPressed(MeJOYSTICK_R1))
  {
    Speed =180;
    Serial.println("L1 is pressed!");
  }
  if (MePS2.ButtonPressed(MeJOYSTICK_R2))
  {
    Speed = 130;
    Serial.println("L2 is pressed!");
  }
  if(loopTime + 500 < millis()){
    RGB_Loop();
    loopTime = millis();
  }
    
}
