#pragma once
#include "Config.h"
#include "Hardware.h"

#define LED_OFF false
#define LED_ON true

class BallTouch : public Hardware
{

public:
    BallTouch(const bool& enabled = false, const int& treshhold = 0)
        {
            _enabled = enabled;
            if(treshhold != 0)
            {
                _threshold = treshhold;
                _calibrated = true;
            }
        };
    void init() override;
    void update() override;

    void calibrate();

    //only call this in combination
    void calibrateNoBall();
    void calibrateBall();
    void calculateTreshold();
    
    const bool getCaliNoBall();
    const bool getCaliBall();
    const bool getCali();

    int getValue();
    int getThreshold();
    int getNoBallThreshold();
    int getBallThreshold();
    bool hasBall();

private:
    int _thresholdNoBall = -1;
    int _thresholdBall = -1;
    int _threshold;

    bool _caliNoBall;
    bool _caliBall;
    bool _calibrated;

    int _summe;
    int _counter;

    int _value;
    int _darkValue;
    int _lightValue;

    unsigned long _offTimer;
    unsigned long _onTimer;

    bool _state = LED_OFF;

    void turnOn();
    void turnOff();
    void calculate();
};

