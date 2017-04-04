#include <Arduino.h>

class ShiftRegister
{
public:
  ShiftRegister(int latch, int data, int clock);
  write(int n,int v);
  update();
private:
  int value;
  int latch;
  int data;
  int clock;
};
