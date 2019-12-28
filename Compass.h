//https://www.robot-electronics.co.uk/files/cmps12.pdf

#pragma once

#include "Config.h"

#define COMPASS_ADRESS 96

class Compass : public Hardware
{

public:
    Compass();
    void init();
    void update();

    float getAngle8();
    int getAngle16();
    int getPitch();
    int getRoll();

private:
    unsigned char _high_byte, _low_byte, _angle8;
    char _pitch, _roll;
    unsigned int _angle16;
};
