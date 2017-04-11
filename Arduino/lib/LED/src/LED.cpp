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

void LED::flash(int freq)
{
  this->freq = freq / 2;
  this->action = 3;
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
    case 0: //Off
      this->sr->write(this->pin,0);
      this->sr->writePWM(this->pin,-1);
      break;
    case 1: //On
      this->sr->write(this->pin,1);
      this->sr->writePWM(this->pin,-1);
      break;
    case 2: //Fade
      this->count += (millis() - this->prev);
      this->prev = millis();
      if(this->count >= this->freq)
      {
        //Increase on Decrease brightness value
        if(this->up)
          this->bright += 1;
        else
          this->bright -=1;

        //Switch directions when an end is reached
        if(this->bright == 31 || this->bright == 0)
          this->up = !this->up;
        this->count = 0;
      }
      this->sr->writePWM(this->pin,this->bright);
      break;
    case 3: //flash
      this->count += (millis() - this->prev);
      this->prev = millis();
      if(this->count >= this->freq)
      {
        //Toggle between of and on
        this->bright = (this->bright == 0) ? 31 : 0;
        this->count = 0;
      }
      break;
  }
}
