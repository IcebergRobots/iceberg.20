#ifndef BallTouch_h
#define BallTouch_h

#include "Config.h"

#define LED_OFF false
#define LED_ON true

class BallTouch
{

public:
    BallTouch();
    void init();
    void calibrate();
    

    void update();

    int getValue();
    int getThreshold();
    int getNoBallThreshold();
    int getBallThreshold();
    bool hasBall();

private:
    int _pinLed;
    int _pinSensor;
    int _value;

    int _thresholdNoBall;
    int _thresholdBall;
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

#endif