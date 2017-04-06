#include <Arduino.h>

#include <ShiftRegister.h>
#include <Inputs.h>
#include <RGB.h>

//Constants
const int AXIS_Z = 2;
const int AXIS_X = 1;
const int AXIS_Y = 0;

//Globals
bool connected = false;

ShiftRegister led(4,2,3);
Inputs in(64,5,&led);

RGB status1(0,1,2,&led);

void setup()
{
    Serial.begin(57600);
    led.setup();
    in.setup();
    Serial.println("R");

    status1.set('r');

}

void loop()
{
    if(Serial.available() > 0)
    {
        char cmd = Serial.read();
        switch(cmd)
        {
            case 0: //Disconnect
                connected = false;
                status1.set('r');
                break;
            case 1: //Connect
                connected = true;
                status1.set('b');
                break;
        }
    }
    if(connected)
    {
        led.tick();
        int val_x = analogRead(AXIS_X);
        //int val_y = analogRead(AXIS_Y);
        //int val_z = analogRead(AXIS_Z);
        Serial.print("ax");
        Serial.println(val_x);
        //Serial.print("ay");
        //Serial.println(val_y);
        //Serial.print("az");
        //Serial.println(val_z);

        led.write(18,0);
        if(in.getState(77)){
          led.write(18,1);
        }

        in.tick();

    }
    led.tick();
}
