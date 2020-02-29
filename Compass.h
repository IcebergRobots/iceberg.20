//https://www.robot-electronics.co.uk/files/cmps12.pdf

#pragma once

#include "Config.h"
#include "Hardware.h"
#include "PID_v1.h"
#include <Adafruit_L3GD20.h>

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

    // void cali();
    // int getAngle();
    // unsigned char getAngle8();
    // int getAngle16();
    // int getPitch();
    // int getRoll();

    // void storeCalibration(); //notworking in the moment
    // void eraseCalibration(); //notworking in the moment

    // bool calibrated;
    // void checkCalibration();

    int getPIDOutput();
    Adafruit_L3GD20 gyro;

    // int getTemperature();
private:
    double _setpoint = 0;    //PID Zielwert
    double _input, _output;          //CMPS Input, rotationsstärke
    PID _myPID = PID(&_input, &_output, &_setpoint, PID_FILTER_P, PID_FILTER_I, PID_FILTER_D, DIRECT);

    // void firstCali();
    // unsigned char _high_byte, _low_byte, _angle8, _high_byteTemp, _low_byteTemp;
    // int _pitch, _roll;
    // unsigned int _angle16;
    // int _temperature;

    // unsigned int _firstOffset; //need this because calibration doesnt work properly
    // unsigned int _offset; //need this because calibration doesnt work properly

    // byte _checkCalibration;
};
