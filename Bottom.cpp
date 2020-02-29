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
    if (getEn())
    {
        bottom.show();
        // if(digitalRead(INT_BODENSENSOR) == HIGH)
        // {
            // _seesLine = false;
            if(Serial3.available() >= 1)
            {
                _seesLine = true;
                _angle = Serial3.read();
                _angle = map(_angle, 0, 255, 0, 360);
                if(_angle < 280 && _angle > 260)
                        _angle = 270;
                else if( _angle < 95 && _angle > 80)
                        _angle = 90;
                else if(_angle > 170 && _angle < 190)
                        _angle = 180;
                    // case _angle < 280 && _angle > 260:
                    //     _angle = 270;
                    //     break;
                }
            }else {
                    _angle = -1;
                    _seesLine = false;
                }
    }


int Bottom::getAngel()
{
    return _angle;
}

// void Bottom::seesLine()
// {
//     _seesLine = true;
// }