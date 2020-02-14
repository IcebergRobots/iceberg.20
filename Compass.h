//https://www.robot-electronics.co.uk/files/cmps12.pdf

#pragma once

#include "Config.h"
#include "Hardware.h"

#define COMPASS_ADRESS 96

class Compass : public Hardware
{

public:
    Compass(const bool& enabled = false)
        {
            _enabled = enabled;
        };
    void init() override;
    void update() override;

    unsigned char getAngle8();
    int getAngle16();
    int getPitch();
    int getRoll();

    bool checkCalibration();
    int getTemperature();
private:
    unsigned char _high_byte, _low_byte, _angle8, _high_byteTemp, _low_byteTemp;
    int _pitch, _roll;
    unsigned int _angle16;
    int _temperature;

    byte _checkCalibration;
};
