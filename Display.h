#pragma once
#include "Player.h"
#include "Nextion.h"

#define NUM_OBJECTS 24

class Display
{
public:
    static void init();
    static void update();

private:
    Display();

    //Overview
    static void goRAM(void *ptr);
    static void goState(void *ptr);

    //Hardware
    static void goHardBallt(void *ptr);
    static void goHardKick(void *ptr);
    static void goHardChassis(void *ptr);

    //Config
    static void goEnDisable(void *ptr);

    //Config calibrate
    static void goCaliKick(void *ptr);

    //Cali ballTouch
    static void ballTouchBall(void *ptr);
    static void ballTouchNoBall(void *ptr);
    static void ballTouchThreshold(void *ptr);

    //Hardware ballTouch

    //Hardware En/Disable
    static void switchEnKick(void *ptr);
    static void switchEnChassis(void *ptr);
    static void switchEnCmps(void *ptr);
    static void switchEnCam(void *ptr);
    static void switchEnUs(void *ptr);
    static void switchEnBallt(void *ptr);
    static void switchEnBt(void *ptr);
    static void switchEnPui(void *ptr);

    //Hardware Kicker
    static void kickBall(void *ptr);
    //static void enKick2(void *ptr); attached switchEnKick

    //Cali Kicker
    //static void kickBall(void *ptr); attached kickBall
    static void kickSlider(void *ptr);

    //Hardware Chassis
    //attach to enChassis

    //Overview
    static NexButton _goRAM;
    static NexButton _goState;

    //Hardware
    static NexButton _goHardBallt;
    static NexButton _goHardKick;
    static NexButton _goHardChassis;

    //Config
    static NexButton _goEnDisable;

    //Config calibrate
    static NexButton _goCaliKick;

    //Calibrate ballTouch
    static bool _caliNoBall;
    static bool _caliBall;
    static NexButton _ballTouchBall;
    static NexButton _ballTouchNoBall;
    static NexButton _ballTouchThreshold;
    static NexText _ballTouchStatus;

    //Hardware ballTouch
    static NexText _ballCali;
    static NexText _ballStatus;
    static NexText _ballText;

    //Hardware Enable/Disable
    static NexDSButton _enKick;
    static NexDSButton _enChassis;
    static NexDSButton _enCmps;
    static NexDSButton _enCam;
    static NexDSButton _enUs;
    static NexDSButton _enBallt;
    static NexDSButton _enBt;
    static NexDSButton _enPui;

    //Hardware Kicker
    static NexButton _kickBall;
    static NexDSButton _enKick2;

    //Cali Kicker
    static NexButton _kickBall2;
    static NexSlider _kickSlider;
    static NexNumber _kickPower;

    //Harware Chassis
    static NexDSButton _enChassis2;

    //Overview FreeRAM
    static NexNumber _freeRAM;

    //Overview State
    static NexText _state;

    static NexTouch *_nex_listen_list[NUM_OBJECTS];
};
