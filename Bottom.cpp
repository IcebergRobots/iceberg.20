#include "Bottom.h"

void Bottom::init()
{
    if (getEn())
    {
        Serial3.begin(115200);
        pinMode(BOTTOM_LED, OUTPUT);
        // pinMode(INT_BODENSENSOR, INPUT);
        // attachInterrupt(digitalPinToInterrupt(INT_BODENSENSOR), seesLine, RISING);
        _bottom.setBrightness(255);
        for (int i = 0; i < 40; i++)
            _bottom.setPixelColor(i, _bottom.Color(255, 255, 255));
    }
}

void Bottom::update()
{
    int minDis = 0;
    if (getEn())
    {
        _bottom.show();
        // if(digitalRead(INT_BODENSENSOR) == HIGH)
        // {
        // _seesLine = false;
        if (Serial3.available() >= 1)
        {
            while (Serial3.available() > 1)
                Serial3.read();
            _seesLine = Serial3.read();
        }
    }
}

void Bottom::setEn(const bool& enabled)
{
    if(!enabled)
    {
        _bottom.setBrightness(0);
        _bottom.show();
    }else {
        _bottom.setBrightness(255);
        for (int i = 0; i < 40; i++)
            _bottom.setPixelColor(i, _bottom.Color(255, 255, 255));
    }
    _enabled = enabled;
}

bool Bottom::seesLine()
{
    return _seesLine;
}
