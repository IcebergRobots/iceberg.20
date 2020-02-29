#include "Bottom.h"

void Bottom::init()
{
    if (getEn())
    {
        Serial3.begin(115200);
        pinMode(BOTTOM_LED, OUTPUT);
        pinMode(INT_BODENSENSOR, INPUT);
        // attachInterrupt(digitalPinToInterrupt(INT_BODENSENSOR), seesLine, RISING);
        bottom.setBrightness(255);
        for (int i = 0; i < 40; i++)
        {
            bottom.setPixelColor(i, bottom.Color(255, 255, 255));
        }
    }
}

void Bottom::update()
{
    if (getEn())
    {
        bottom.show();
        // if(digitalRead(INT_BODENSENSOR) == HIGH)
        // {
            // _seesLine = false;
            if(Serial3.available() >= 1)
            {
                _angle = map(Serial3.read(), 0, 255, 0, 360);
            }else{
                Serial.println("No lIne");
            }
        // }
    }
}

int Bottom::getAngel()
{
    return _angle;
}

void Bottom::seesLine()
{
    _seesLine = true;
}