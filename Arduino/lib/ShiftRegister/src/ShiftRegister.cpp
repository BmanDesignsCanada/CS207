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

  for(int i = 0; i < 55; i++)
  {
    this->pwm[i] = -1;
  }
}

void ShiftRegister::write(int n, int v)
{
  //Change a single bit value
  set(n, v);
}

void ShiftRegister::writePWM(int n, int v)
{
  this->pwm[n] = v;
}

void ShiftRegister::tick()
{
  for(int i = 0; i < 55; i++){
    //check if pwm has been disabled on the pin
    if(this->pwm[i] != -1){
      if(this->pwm[i] > l)
      {
        set(i,1);
      }else{
        set(i,0);
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
  shiftOut(this->data, this->clock, MSBFIRST, this->value5 >> 8);
  shiftOut(this->data, this->clock, MSBFIRST, this->value5);
  shiftOut(this->data, this->clock, MSBFIRST, this->value4 >> 8);
  shiftOut(this->data, this->clock, MSBFIRST, this->value4);
  shiftOut(this->data, this->clock, MSBFIRST, this->value3 >> 8);
  shiftOut(this->data, this->clock, MSBFIRST, this->value3);
  shiftOut(this->data, this->clock, MSBFIRST, this->value2 >> 8);
  shiftOut(this->data, this->clock, MSBFIRST, this->value2);
  shiftOut(this->data, this->clock, MSBFIRST, this->value >> 8);
  shiftOut(this->data, this->clock, MSBFIRST, this->value);
  //Display the value
  digitalWrite(this->latch, HIGH);
}

void ShiftRegister::set(int pin, int v)
{
  switch (pin) {
    case 0 ... 15:
      this->value = bitWrite(this->value,pin,v);
      break;
    case 16 ... 31:
      this->value2 = bitWrite(this->value2,pin-16,v);
      break;
    case 32 ... 47:
      this->value3 = bitWrite(this->value3,pin-32,v);
      break;
    case 48 ... 63:
      this->value4 = bitWrite(this->value4,pin-48,v);
      break;
    default:
      this->value5 = bitWrite(this->value5,pin-64,v);
      break;
  }
}
