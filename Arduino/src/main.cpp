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
/*LED b3(10,&led);
LED b4(11,&led);
LED b5(12,&led);
LED b6(13,&led);
LED b7(14,&led);
LED b8(15,&led);
LED b9(16,&led);
LED b10(17,&led);
LED b11(18,&led);*/
LED b12(19,&led);

void setup()
{
  Serial.begin(57600);
  led.setup();
  in.setup();
  Serial.println("R");

  status1.set('g');
  b2.fade(1000);
  led.writePWM(13,5);
}

void loop()
{
  if(Serial.available() > 0)
  {
    switch(Serial.read())
    {
      case 0: //Disconnect
        connected = false;
        status1.set('r');
        break;
      case 1: //Connect
        connected = true;
        status1.set('y');
        //b2.fade(550);
        /*b3.fade(600);
        b4.fade(650);
        b5.fade(700);
        b6.fade(750);
        b7.fade(800);
        b8.fade(850);
        b9.fade(900);
        b10.fade(500);
        b11.fade(1000);*/
        //b12.fade(1000);
        break;
    }
  }
  if(connected)
  {
    led.tick();

    //Check which way to install josytick next time
    /*Serial.print("ax");
    Serial.println(map(analogRead(2),0,1024,1024,0));
    Serial.print("ay");
    Serial.println(map(analogRead(1),0,1024,1024,0));*/
    //Serial.print("az");
    //Serial.println(map(analogRead(0),0,1024,1024,0));

    //led.write(9,1);
    b2.tick();
    led.tick();
    /*b3.tick();
    led.tick();
    b4.tick();
    led.tick();
    b5.tick();
    led.tick();
    b6.tick();
    led.tick();
    b7.tick();
    led.tick();
    b8.tick();
    led.tick();
    b9.tick();
    led.tick();
    b10.tick();
    led.tick();
    b11.tick();
    led.tick();*/
    //b12.tick();
    //led.tick();

    //in.tick();
  }
  b2.tick();
  led.tick();
}
