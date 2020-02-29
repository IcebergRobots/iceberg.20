#include "Bottom.h"

extern Ultrasonic us();

int distance[] = {us.getBack(), us.getLeft(), us.getRight(), us.getFrontLeft()};
int anglesUS[] = {0, 270, 90, 180};

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
                for (int i = 0; i < 4; i++){
                    if(minDis > distance[i]){
                        minDis = distance[i];
                        _angle = anglesUS[i];
                    }
                }us.getBack()
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