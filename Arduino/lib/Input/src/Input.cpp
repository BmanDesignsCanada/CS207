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
  this->sr->write(this->id,1);
  this->sr->update();
  bool cur = digitalRead(this->pin);
  this->sr->write(this->id,0);
  if (cur == state)
  {
    waitTime = 0;
    prev = millis();
  }
  else
  {
    waitTime += millis() - prev;
    prev = millis();
  }
  if(waitTime >= 0)
  {
    state = cur;
    //Serial.print((char)id);
    //Serial.println((int)cur);
  }
}
