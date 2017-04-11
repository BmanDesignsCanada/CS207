#include <Arduino.h>
#include <Input.h>
#include <ShiftRegister.h>

/*
  Library used to manage multiple Inputs
  only checks one button every tick
*/

class Inputs
{
public:
  Inputs(int start, int pin, ShiftRegister* sr);
  bool getState(int id);
  void setLed(int id, bool state);
  void tick();
  void setup();
private:
  int state = 0;
  Input* inputs[16];
  ShiftRegister* sr;
  int start;
};
