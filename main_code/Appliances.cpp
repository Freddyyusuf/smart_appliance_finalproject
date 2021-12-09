#include "Appliance.h"

Appliance::Appliance(byte pin, unsigned int timeOut) {
  this->pin = pin;
  this->timeOut= timeOut;
  init();
}

void Appliance::init() {
  state= 0;
  pinMode(pin, OUTPUT);
}

void Appliance::on() {
  state= 1;
  digitalWrite(pin, state);
}

void Appliance::off() {
  state= 0;
  digitalWrite(pin, state);
}

void Appliance::processTimeOut(byte triggerPin){
  boolean Reading= digitalRead(triggerPin);
  if (Reading){
    if (millis() - lastDetectedTime > timeOut) {
      off();
    }
    
  } else lastDetectedTime = millis();
}



byte Appliance::getState() {
  return state;
}
