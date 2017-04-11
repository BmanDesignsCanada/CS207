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
  //Converts a 256 point color in a 32 point color
  set32(
    map(r,0,255,0,31),
    map(g,0,255,0,31),
    map(b,0,255,0,31)
  );
}

void RGB::set32(int r, int g, int b)
{
  //Set the color from an rgb value
  this->sr->writePWM(this->r,r);
  this->sr->writePWM(this->g,g);
  this->sr->writePWM(this->b,b);
}

void RGB::set(char color)
{
  switch(color)
  {
    case 'y': //Yellow
      set32(16, 0, 31);
      break;
    case 'b': //Blue
      set32(0, 0, 31);
      break;
    case 'r': //Red
      set32(31, 0, 0);
      break;
    case 'g': //Green
      set32(0, 31, 0);
      break;
    case 'p': //Purple
      set32(31, 31, 31); //Not actually purple yet
      break;
    case 'w': //White
      set32(31, 31, 31);
      break;
    case 'o': //Orange
      set32(31, 31, 31); //Not actually orange yet
      break;
    case '0': //Off
      set32(0, 0, 0);
      break;
  }
}
