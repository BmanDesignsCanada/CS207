#include <Arduino.h>
#include <ShiftRegister.h>

class RGB
{
public:
  RGB(int r, int g, int b, ShiftRegister* sr);
  void set256(int r, int g, int b);
  void set32(int r, int g, int b);
  void set(char color);
private:
  int r;
  int g;
  int b;
  ShiftRegister* sr;
};
