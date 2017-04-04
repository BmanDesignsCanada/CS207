#include <Arduino.h>

#include <ShiftRegister.h>

//Constants
const int AXIS_Z = 2;
const int AXIS_X = 1;
const int AXIS_Y = 0;

const int BTN_JOYSTICK = 5;
const int BTN_A = 3;
const int BTN_B = 4;

//Globals
bool connected = false;

ShiftRegister statusLEDs(4,2,3);

void setup()
{
    Serial.begin(57600);

    pinMode(LED_CONNECTED, OUTPUT);
    pinMode(BTN_JOYSTICK, INPUT);
    pinMode(BTN_A, INPUT);
    pinMode(BTN_B, INPUT);
    Serial.println("R");
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
                statusLEDs.write(0,false);
                break;
            case 1: //Connect
                connected = true;
                statusLEDs.write(0,true);
                break;
        }
        statusLEDs.update();
    }
    if(connected)
    {
        int val_x = analogRead(AXIS_X);
        int val_y = analogRead(AXIS_Y);
        int val_z = analogRead(AXIS_Z);

        Serial.print("x");
        Serial.println(val_x);
        Serial.print("y");
        Serial.println(val_y);
        Serial.print("z");
        Serial.println(val_z);
        Serial.print("j");
        Serial.println(abs(digitalRead(BTN_JOYSTICK) - 1));
        Serial.print("a");
        Serial.println(abs(digitalRead(BTN_A) - 1));
        Serial.print("b");
        Serial.println(abs(digitalRead(BTN_B) - 1));
    }
    statusLEDs.tick();
}
