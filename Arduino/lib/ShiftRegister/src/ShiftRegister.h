#ifndef ShiftRegister_H
#define ShiftRegister_H

#include <Arduino.h>

class ShiftRegister
{
public:
  ShiftRegister(int latch, int data, int clock);
  void setup();
  void write(int n, int v);
  void writePWM(int n, int v);
  void tick();
  void update();
private:
  int pwm[48];
  unsigned int value = 0;
  int latch;
  int data;
  int clock;
  int l = 0;
};

#endif
