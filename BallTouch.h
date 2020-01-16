#pragma once
#include "Config.h"
#include "Hardware.h"

#define LED_OFF false
#define LED_ON true

class BallTouch : public Hardware
{

public:
    BallTouch();
    void init() override;
    void calibrate();

    //only call this in combination
    void calibrateNoBall();
    void calibrateBall();
    void calculateTreshold();

    void update() override;

    int getValue();
    int getThreshold();
    int getNoBallThreshold();
    int getBallThreshold();
    bool hasBall();

private:
    int _pinLed;
    int _pinSensor;
    int _value;

    int _thresholdNoBall = -1;
    int _thresholdBall = -1;
    int _threshold;

    int _summe;
    int _counter;

    int _darkValue;
    int _lightValue;

    unsigned long _offTimer = 0;
    unsigned long _onTimer = 0;

    bool _state = LED_OFF;

    void turnOn();
    void turnOff();
    void calculate();
};

