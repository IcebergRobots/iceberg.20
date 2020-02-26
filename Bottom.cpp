#include "Bottom.h"

void Bottom::init()
{
    if (getEn())
    {
        pinMode(BOTTOM_LED, OUTPUT);
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
    }
}