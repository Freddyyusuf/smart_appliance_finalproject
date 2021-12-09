#include "Button.h"

Button::Button(byte pin) {
  this->pin = pin;
  lastReading = LOW;
  init();
}

void Button::init() {
  pinMode(pin, INPUT);
  update();
}

void Button::update() {
    byte newReading = digitalRead(pin);
    
    if (newReading != lastReading) {
      lastDebounceTime = millis();
    }

    if (millis() - lastDebounceTime > debounceDelay) {
      state = newReading;
    }

    lastReading = newReading;
}

byte Button::toggle(){
  int tglState= isPressed();
  if (tglState!=tglStateBefore){
    tglStateBefore= tglState;
    if(tglState){
      toggleState= !toggleState;
    }
  }
  return toggleState;
}

byte Button::getState() {
  update();
  return state;
}

bool Button::isPressed() {
  return (getState() == HIGH);
}
