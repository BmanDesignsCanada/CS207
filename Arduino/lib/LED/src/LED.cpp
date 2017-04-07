#include "LED.h"

LED::LED(int pin, ShiftRegister* sr)
{
  this->pin = pin;
  this->sr = sr;
}

LED::LED(int pin, int btn, ShiftRegister* sr)
{
  this->pin = pin;
  this->btn = btn;
  this->sr = sr;
}

/*LED::LED(RGB* led, ShiftRegister* sr)
{
  this->led = led;
  this->sr = sr;
}*/

void LED::fade(int freq)
{
  this->freq = freq / 32;
  this->action = 2;
}

void LED::on()
{
  this->action = 1;
}

void LED::off()
{
  this->action = 0;
}

void LED::tick()
{
  switch(action)
  {
    case 0:
      this->sr->write(this->pin,0);
      break;
    case 1:
      this->sr->write(this->pin,1);
      break;
    case 2: //Fade
      this->count += (millis() - this->prev);
      this->prev = millis();
      if(this->count >= this->freq)
      {
        if(this->up)
          this->bright += 1;
        else
          this->bright -=1;
        if(this->bright == 31 || this->bright == 0)
          this->up = !this->up;
        this->count = 0;
      }
      this->sr->writePWM(this->pin,this->bright);
      break;
  }
}
