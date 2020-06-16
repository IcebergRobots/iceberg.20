//https://www.robot-electronics.co.uk/files/cmps12.pdf

#pragma once

#include "Config.h"
#include "Hardware.h"
#include "PID_v1.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_LSM303_U.h"
#include "Adafruit_L3GD20.h"
#include "Adafruit_9DOF.h"
#include "Adafruit_BNO055.h"

#define COMPASS_ADRESS 96

// PID-Regler
#define PID_FILTER_P 0.3   //p:proportional
#define PID_FILTER_I 0 //i:vorausschauend 
#define PID_FILTER_D 0.05  //d:Schwung herausnehmen (nicht zu weit drehen)

class Compass : public Hardware
{

public:
    Compass(const bool& enabled = false)
        {
            _enabled = enabled;
        };

    void init() override;
    void update() override;

    void cali();
    int getAngle();
    // unsigned char getAngle8();
    // int getAngle16();
    int getPitch();
    int getRoll();

    // void storeCalibration(); //notworking in the moment
    // void eraseCalibration(); //notworking in the moment

    // bool calibrated;
    // void checkCalibration();

    int getPIDOutput();

    // int getTemperature();
private:
    Adafruit_9DOF dof = Adafruit_9DOF();
    Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(30302);
    Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);

    sensors_event_t accel_event;
    sensors_event_t mag_event;
    sensors_vec_t   orientation;

    Adafruit_BNO055 bno = Adafruit_BNO055(55);

    double _setpoint = 0;    //PID Zielwert
    double _input, _output;          //CMPS Input, rotationsstärke
    PID _myPID = PID(&_input, &_output, &_setpoint, PID_FILTER_P, PID_FILTER_I, PID_FILTER_D, DIRECT);
    int _median[3] = {0,0,0};
    int _count;

    int _medianPitch[3];
    int _angle;
    // void firstCali();
    // unsigned char _high_byte, _low_byte, _angle8, _high_byteTemp, _low_byteTemp;
    int _pitch, _roll;
    // unsigned int _angle16;
    // int _temperature;

    // unsigned int _firstOffset; //need this because calibration doesnt work properly
    unsigned int _offset; //need this because calibration doesnt work properly

    // byte _checkCalibration;
};
