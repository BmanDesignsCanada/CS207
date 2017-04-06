#include "RGB.h"

RGB::RGB(int r, int g, int b, ShiftRegister* sr)
{
  this->r = r;
  this->g = g;
  this->b = b;
  this->sr = sr;
}

void RGB::set256(int r, int g, int b)
{
  set32(
    map(r,0,255,0,31),
    map(g,0,255,0,31),
    map(b,0,255,0,31)
  );
}

void RGB::set32(int r, int g, int b)
{
  this->sr->writePWM(this->r,r);
  this->sr->writePWM(this->g,g);
  this->sr->writePWM(this->b,b);
}

void RGB::set(char color)
{
  switch(color)
  {
    case 'y': //Yellow
      this->sr->writePWM(this->r,31);
      this->sr->writePWM(this->g,31);
      this->sr->writePWM(this->b,31);
      break;
    case 'b': //Blue
      this->sr->writePWM(this->r,0);
      this->sr->writePWM(this->g,0);
      this->sr->writePWM(this->b,31);
      break;
    case 'r': //Red
      this->sr->writePWM(this->r,31);
      this->sr->writePWM(this->g,0);
      this->sr->writePWM(this->b,0);
      break;
    case 'g': //Green
      this->sr->writePWM(this->r,0);
      this->sr->writePWM(this->g,31);
      this->sr->writePWM(this->b,0);
      break;
    case 'p': //Purple
      this->sr->writePWM(this->r,31);
      this->sr->writePWM(this->g,31);
      this->sr->writePWM(this->b,31);
      break;
    case 'w': //White
      this->sr->writePWM(this->r,31);
      this->sr->writePWM(this->g,31);
      this->sr->writePWM(this->b,31);
      break;
    case 'o': //Orange
      this->sr->writePWM(this->r,31);
      this->sr->writePWM(this->g,31);
      this->sr->writePWM(this->b,31);
      break;
    case '0': //Off
      this->sr->writePWM(this->r,0);
      this->sr->writePWM(this->g,0);
      this->sr->writePWM(this->b,0);
      break;
  }
}
