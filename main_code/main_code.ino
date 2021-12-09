#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include "Button.h"
#include "Appliance.h"

#define BTN_lamp 10
#define BTN_fan 9
#define Lamp_PIN  8
#define Fan_PIN  7
#define SensorHuman 11
#define sensorPin A0

float suhuC = 0;
int suhu = 0;

unsigned int timeOutDevice= 5000;

LiquidCrystal_I2C lcd(0x27, 16, 2);
Button btn_lamp(BTN_lamp);
Button btn_fan(BTN_fan);
Appliance Lamp(Lamp_PIN, timeOutDevice);
Appliance Fan(Fan_PIN, timeOutDevice);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();


  pinMode(sensorPin, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("--Smart Room--"); //atau apalah itu namanya gatau pusing 
  lcd.setCursor(0, 1);
  lcd.print("-----------");
  delay(2000);
  lcd.clear();
}

void loop() {
  int detectionValid= digitalRead(SensorHuman);
  
  suhu = analogRead(sensorPin);
  suhuC = (suhu)*(0.4848);
  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  lcd.print(suhuC);
  lcd.print("@C");
  
  Serial.println(suhu);
  
  Serial.print(btn_fan.toggle());
  Serial.print(" F-------L ");
  Serial.print(btn_lamp.toggle());
  Serial.print(" ======V ");
  Serial.println(detectionValid);
  
  Lamp.processTimeOut(detectionValid);
  Fan.processTimeOut(detectionValid);
  
  if (detectionValid){
    
    if (btn_lamp.toggle()){
      Lamp.on();
    } else Lamp.off();
    
    if (suhuC >= 30 && btn_fan.toggle()) {
      Fan.on();
      
    } else {
      Fan.off();
    }
    
  } 
     
  
}
