#include "Arduino.h"

//Constants
const int Axis_X = 1;
const int Axis_Y = 0;

void setup()
{
    Serial.begin(57600);
}

void loop()
{
    int val_x = analogRead(Axis_X);
    int val_y = analogRead(Axis_Y);

    Serial.print("x");
    Serial.println(val_x);
    Serial.print("y");
    Serial.println(val_y);
}
