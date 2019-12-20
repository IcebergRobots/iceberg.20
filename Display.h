#ifndef Display_h
#define Display_h

#include "Config.h"

#define NUM_OBJECTS 10

class Display
{
public:
    static void init();
    static void update();
private:
Display();

    //Example
    static void bLedOnPopCallback(void *ptr);
    static void bLedOffPopCallback(void *ptr);
    static void hLedSliderPopCallback(void *ptr);

    //Cali ballTouch
    static void ballTouchBall(void *ptr);
    static void ballTouchNoBall(void *ptr);
    static void ballTouchThreshold(void *ptr);

    //Sensor ballTouch
    static void updateBallStatus(void *ptr);

    //Sensor En/Disable
    static void switchEnKick(void *ptr);
    static void enMotors(void *ptr);

    //Beispiel Objects
    static NexText _tLedState;
    static NexButton _bLedOn;
    static NexButton _bLedOff;
    static NexSlider _hLedSlider;
    static const int _led1 = 6;

    //Calibrate ballTouch
    static NexButton _ballTouchBall;
    static NexButton _ballTouchNoBall;
    static NexButton _ballTouchThreshold;
    static NexText _ballTouchStatus;

    //Sensor ballTouch
    static NexText _caliStatus;
    static NexText _ballStatus;
    static NexButton _updateStatus;

    //Sensor Enable/Disable
    static NexDSButton _enKick;
    static NexDSButton _enMotors;

    static NexTouch *_nex_listen_list[NUM_OBJECTS];

};
#endif
