#include <Arduino.h>
#include <RGB.h>
#include <ShiftRegister.h>

/*
  Library to support individual LEDs
*/

class LED
{
public:
  LED(int pin, ShiftRegister* sr);
  LED(int pin, int btn, ShiftRegister* sr);
  //LED(RGB* led, ShiftRegister* sr);

  void fade(int freq);
  void flash(int freq);
  void on();
  void off();

  void tick();

private:
  int pin;
  int btn;
  RGB* led;
  ShiftRegister* sr;

  unsigned int prev = 0;
  unsigned int count = 0;

  int action = 0;
  unsigned int freq = 500;
  int bright = 0;
  bool up = true;
};
