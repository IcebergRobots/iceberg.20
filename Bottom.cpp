#include "Bottom.h"

void Bottom::init()
{
    if (getEn())
    {
        pinMode(BOTTOM_LED, OUTPUT);
        // pinMode(INT_BODENSENSOR, INPUT);
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
    int minDis = 0; 
    if (getEn())
    {
        bottom.show();
        // if(digitalRead(INT_BODENSENSOR) == HIGH)
        // {
            // _seesLine = false;
            if(Serial3.available() >= 1)
            {
                while (Serial3.available() > 1)
                {
                    Serial3.read();
                }
                _seesLine = true;
            }else {
                //_angle = -1;
                _seesLine = false;
            }
    }

}

int Bottom::getAngel()
{
    return _angle;
}

bool Bottom::seesLine()
{
    return _seesLine;
}

// void Bottom::seesLine()
// {
//     _seesLine = true;
// }