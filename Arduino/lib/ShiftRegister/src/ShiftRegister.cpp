#include "ShiftRegister.h"

static inline void latchPinH()  {bitSet(PORTB,0);}
static inline void latchPinL()  {bitClear(PORTB,0);}
static inline void clockPinH()  {bitSet(PORTB,4);}
static inline void clockPinL()  {bitClear(PORTB,4);}
static inline void dataPinH()   {bitSet(PORTB,2);}
static inline void dataPinL()   {bitClear(PORTB,2);}

void fastShiftOut(unsigned int b){
  clockPinL();
  dataPinL();
  for (int i=7; i>=0; i--){
    if (bitRead(b,i) == 1) dataPinH();
    else dataPinL();
    clockPinH();
    clockPinL();
  }
}

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
  fastShiftOut(this->value5 >> 8);
  fastShiftOut(this->value5);
  fastShiftOut(this->value4 >> 8);
  fastShiftOut(this->value4);
  fastShiftOut(this->value3 >> 8);
  fastShiftOut(this->value3);
  fastShiftOut(this->value2 >> 8);
  fastShiftOut(this->value2);
  fastShiftOut(this->value >> 8);
  fastShiftOut(this->value);
  //Display the value
  digitalWrite(this->latch, HIGH);
}

void ShiftRegister::set(int pin, int v)
{
  if (pin < 16)
    this->value = bitWrite(this->value,pin,v);
  else if (pin < 32)
    this->value2 = bitWrite(this->value2,pin-16,v);
  else if (pin < 48)
    this->value3 = bitWrite(this->value3,pin-32,v);
  else if (pin < 64)
    this->value4 = bitWrite(this->value4,pin-48,v);
  else
    this->value5 = bitWrite(this->value5,pin-64,v);
}
