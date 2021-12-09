#ifndef MY_APP_H
#define MY_APP_H

#include <Arduino.h>

class Appliance {
  
  private:
    byte pin;
    byte state;
    byte triggerPin;
    unsigned long timeOut= 1000;
    unsigned long lastDetectedTime = 0;
    
    
  public:
    Appliance(byte pin, unsigned int timeOut);

    void init();
    void on();
    void off();
    void processTimeOut(byte triggerPin) ;
    byte getState();

};

#endif
