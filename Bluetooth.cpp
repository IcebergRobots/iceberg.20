#include "Bluetooth.h"

void Bluetooth::init()
{
    if (getEn())
    {
        if (!Serial2)
            Serial.println("Serial2 couldnt Open");
        Serial2.begin(115200);
    }
}

void Bluetooth::update()
{
    if(getEn())
    {
        if(Serial2.available())
            b = Serial2.read();        
    }
}

void Bluetooth::send()
{
    if(getEn())
    {
        
    }
}

void Bluetooth::receive()
{
    if(getEn())
    {
        
    }
}