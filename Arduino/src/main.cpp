#include <Arduino.h>
#include <ShiftRegister.h>
#include <Inputs.h>
#include <RGB.h>
#include <LED.h>

//Globals
bool connected = false;

ShiftRegister led(8,10,12);
Inputs in(64,5,&led);

RGB status1(0,1,2,&led);

//LED b1(8,&led);
LED b2(9,&led);
LED b3(10,&led);
LED b4(11,&led);
LED b5(12,&led);
LED b6(13,&led);
LED b7(14,&led);
LED b8(15,&led);
LED b9(16,&led);
LED b10(17,&led);
LED b11(18,&led);
LED b12(19,&led);

int demo = 1;
int stage = 0;
unsigned long prev = 0;
unsigned int count = 0;
bool last = false;

void allOff()
{
  //Turn all the LEDs off
  b2.off();
  b3.off();
  b4.off();
  b5.off();
  b6.off();
  b7.off();
  b8.off();
  b9.off();
  b10.off();
  b11.off();
  b12.off();
}

void setup()
{
  Serial.begin(57600);
  led.setup();
  in.setup();
  Serial.println("R");
  //set the status led to red
  status1.set('r');
}

void receiveCommands()
{
  if(Serial.available() > 0)
  {
    switch(Serial.read())
    {
      case 0: //Disconnect
        connected = false;
        //set the status led to red
        status1.set('r');
        break;
      case 1: //Connect
        connected = true;
        //set the status led to yellow
        status1.set('y');
        break;
    }
  }
}

void sendJoystick()
{
  //Read joystick positions and invert the data
  led.tick(); //analogRead is really slow
  Serial.print("ax");
  Serial.println(map(analogRead(0),0,1024,1024,0)); //Check which way to install josytick next time
  led.tick();
  Serial.print("ay");
  Serial.println(map(analogRead(1),0,1024,1024,0));
  led.tick();
  Serial.print("az");
  Serial.println(map(analogRead(2),0,1024,1024,0));
  led.tick();
}

void loop()
{
  receiveCommands();
  if(connected)
  {
    sendJoystick();
  }
  in.tick();

  //LED Demonstation
  switch(demo)
  {
    case 1: //fade
      b2.fade(1000);
      b3.fade(900);
      b4.fade(650);
      b5.fade(700);
      b6.fade(250);
      b7.fade(800);
      b8.fade(450);
      b9.fade(900);
      b10.fade(500);
      b11.fade(1000);
      b12.fade(100);
      break;
    case 2: //loop around
      allOff();
      switch(stage)
      {
        case 0:
          b7.on();
          b8.on();
          break;
        case 1:
          b6.on();
          b9.on();
          break;
        case 2:
          b4.on();
          b11.on();
          break;
        case 3:
          b3.on();
          b12.on();
          break;
        case 4:
          b5.on();
          b10.on();
          break;
      }
      count += millis() - prev;
      prev = millis();
      if(count >= 100)
      {
        count = 0;
        stage++;
        if (stage == 5)
          stage = 0;
      }
      break;
  }

  //if button #69 is pushed change Demonstation
  if(in.getState(69) && !last)
  {
    demo++;
    if (demo == 3){
      demo = 1;
    }
  }
  last = in.getState(69);

  b2.tick();
  b3.tick();
  b4.tick();
  b5.tick();
  b6.tick();
  b7.tick();
  b8.tick();
  b9.tick();
  b10.tick();
  b11.tick();
  b12.tick();
  led.tick();
}
