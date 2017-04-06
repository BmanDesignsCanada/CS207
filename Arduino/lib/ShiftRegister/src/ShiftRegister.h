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
  int pwm[55];
  unsigned int value = 0;
  unsigned int value2 = 0;
  unsigned int value3 = 0;
  unsigned int value4 = 0;
  unsigned int value5 = 0;
  int latch;
  int data;
  int clock;
  int l = 0;
  void set(int pin, int v);
};

#endif
