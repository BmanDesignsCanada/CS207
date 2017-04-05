#include "ShiftRegister.h"

ShiftRegister::ShiftRegister(int latch, int data, int clock)
{
  //Save variables inside object
  this->latch = latch;
  this->data  = data;
  this->clock = clock;
}

void ShiftRegister::setup()
{
  //Set pins to OUTPUT
  pinMode(latch,  OUTPUT);
  pinMode(data,   OUTPUT);
  pinMode(clock,  OUTPUT);

  for(int i = 0; i < 48; i++)
  {
    this->pwm[i] = -1;
  }
}

void ShiftRegister::write(int n, int v)
{
  //Change a single bit value
  value = bitWrite(value, n, v);
}

void ShiftRegister::writePWM(int n, int v)
{
  this->pwm[n] = v;
}

void ShiftRegister::tick()
{
  for(int i = 0; i < 48; i++){
    //check if pwm has been disabled on the pin
    if(this->pwm[i] != -1){
      if(this->pwm[i] > l)
      {
        this->value = bitWrite(this->value,i,1);
      }else{
        this->value = bitWrite(this->value,i,0);
      }
    }
  }
  update();
  l += 1;
  if (l==32){
    l = 0;
  }
}

void ShiftRegister::update()
{
  //Set the shift register latch to low for updating
  digitalWrite(this->latch, LOW);
  //Send data to shift register
  shiftOut(this->data, this->clock, MSBFIRST, this->value >> 8);
  shiftOut(this->data, this->clock, MSBFIRST, this->value);
  //Display the value
  digitalWrite(this->latch, HIGH);
}
