#pragma once
#include "Player.h"
#include "Nextion.h"

#define NUM_OBJECTS 13

class Display
{
public:
    static void init();
    static void update();

private:
    Display();

    //Overview
    static void goRAM(void *ptr);

    //Cali ballTouch
    static void ballTouchBall(void *ptr);
    static void ballTouchNoBall(void *ptr);
    static void ballTouchThreshold(void *ptr);

    //Hardware ballTouch
    static void updateBallTimer(void *ptr);

    //Hardware En/Disable
    static void switchEnKick(void *ptr);
    static void enMotors(void *ptr);
    static void updateEnPage(void *ptr);

    //Hardware Kicker
    static void kickBall(void *ptr);
    //static void enKick2(void *ptr); attached switchEnKick

    //Cali Kicker
    //static void kickBall(void *ptr); attached kickBall
    static void kickSlider(void *ptr);

    //Hardware Motors
    //attach to enMotors

    //Overview
    static NexButton _goRAM;

    //Overview FreeRAM
    static NexText _freeRAM;

    //Calibrate ballTouch
    static NexButton _ballTouchBall;
    static NexButton _ballTouchNoBall;
    static NexButton _ballTouchThreshold;
    static NexText _ballTouchStatus;

    //Hardware ballTouch
    static NexText _ballStatus;
    static NexPage _updateBallStatus;

    //Hardware Enable/Disable
    static NexDSButton _enKick;
    static NexDSButton _enMotors;
    static NexPage _updateEnPage;

    //Hardware Kicker
    static NexButton _kickBall;
    static NexDSButton _enKick2;

    //Cali Kicker
    static NexButton _kickBall2;
    static NexSlider _kickSlider;

    //Harware Motors
    static NexDSButton _enMotors2;

    static NexTouch *_nex_listen_list[NUM_OBJECTS];
};
