#include <Arduino.h>
#include <ShiftRegister.h>

class Input
{
public:
  Input();
  Input(int id, int led, int pin, ShiftRegister* sr);
  void setLed(bool state);
  bool getState();
  void tick();
  void setup();
private:
  int id;
  int pin;
  int led;
  int waitTime;
  bool state;
  unsigned long prev;
  ShiftRegister* sr;
};
