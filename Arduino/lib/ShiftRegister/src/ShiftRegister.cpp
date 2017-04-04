#include "ShiftRegister.h"

ShiftRegister::ShiftRegister(int latch, int data, int clock)
{
  //Set pins to OUTPUT
  pinMode(latch,  OUTPUT);
  pinMode(data,   OUTPUT);
  pinMode(clock,  OUTPUT);

  //Save variables inside object
  this->latch = latch;
  this->data  = data;
  this->clock = clock;
  //Default all lights off
  this->value = 0;
}

ShiftRegister::write(int n, bool v)
{
  //Change a single bit value
  bitWrite(this->value, n, (v) ? 1 : 0);
}

ShiftRegister::update()
{
  //Set the shift register latch to low for updating
  digitalWrite(this->latch, LOW);
  //Send data to shift register
  shiftOut(this->data, this->clock, MSBFIRST, this->value);
  //Display the value
  digitalWrite(this->latch, HIGH);
}
