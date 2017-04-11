#include "Input.h"

Input::Input(int id, int led, int pin, ShiftRegister* sr)
{
  this->id  = id;
  this->led = led;
  this->pin = pin;
  this->sr  = sr;
}

void Input::setup()
{
  pinMode(this->id,OUTPUT);
}

void Input::setLed(bool state)
{
  this->sr->write(this->led,state);
}

bool Input::getState()
{
  return this->state;
}

void Input::tick()
{
  //Set reference voltage to HIGH
  this->sr->write(this->id,1);
  this->sr->update();
  //Check if button is pressed
  bool cur = digitalRead(this->pin);
  //Set reference voltage to GND
  this->sr->write(this->id,0);
  if (cur == state)
  {
    //Reset timer if button state has not changed
    waitTime = 0;
    prev = millis();
  }
  else
  {
    //Debounce timer
    waitTime += millis() - prev;
    prev = millis();
  }
  //Wait for debounce timer before considering the button pushed
  if(waitTime >= 25)
  {
    state = cur;
    //Send codes to control software
    Serial.print('b');
    Serial.print((char)id);
    Serial.println((int)cur);
  }
}
