#include "Inputs.h"

Inputs::Inputs(int start, int pin, ShiftRegister* sr)
{
  this->sr = sr;
  this->start = start;
  for(int i = 0; i < 16; i++)
  {
    this->inputs[i] = new Input(start+i,0, pin, sr);
  }
  pinMode(pin,INPUT);
}

void Inputs::setup()
{
  for(int i = 0; i < 16; i++)
  {
    this->inputs[i]->setup();
  }
}

bool Inputs::getState(int id)
{
  return this->inputs[id-start]->getState();
}

void Inputs::setLed(int id, bool state)
{
  this->inputs[id-start]->setLed(state);
}

void Inputs::tick()
{
  this->inputs[state]->tick();
  state++;
  if(state == 16)
  {
    state = 0;
  }
}
