#include <Arduino.h>

class ShiftRegister
{
public:
  ShiftRegister(int latch, int data, int clock);
  void setup();
  void write(int n,bool v);
  void writePWM(int n, int v);
  void tick();
private:
  void update();

  int pwm[16];
  int value;
  int latch;
  int data;
  int clock;
};
