#include "ShiftRegister.h"

ShiftRegister::ShiftRegister(int latch, int data, int clock)
{
  //Save variables inside object
  this->latch = latch;
  this->data  = data;
  this->clock = clock;
  //Default all lights off
  this->value = 0;
}

void ShiftRegister::setup()
{
    //Set pins to OUTPUT
    pinMode(latch,  OUTPUT);
    pinMode(data,   OUTPUT);
    pinMode(clock,  OUTPUT);
}

void ShiftRegister::write(int n, bool v)
{
  //Change a single bit value
  bitWrite(this->value, n, (v) ? 1 : 0);
}

void ShiftRegister::writePWM(int n, int v)
{
  this->pwm[n] = v;
}

void ShiftRegister::tick()
{
  for(int i = 0; i < 32; i++)
  {
    for(int l = 0; l < 16; l++){
      if(this->pwm[l] >= i)
      {
        bitWrite(this->value,l,1);
      }else{
        bitWrite(this->value,l,0);
      }
    }
    update();
  }
}

void ShiftRegister::update()
{
  //Set the shift register latch to low for updating
  digitalWrite(this->latch, LOW);
  //Send data to shift register
  shiftOut(this->data, this->clock, MSBFIRST, this->value);
  //Display the value
  digitalWrite(this->latch, HIGH);
}
