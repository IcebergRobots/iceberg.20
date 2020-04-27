#pragma once

#include "Display.h"
#include "Ultrasonic.h"
#include "Compass.h"
#include "Utility.h"
#include "Pui.h"
#include "Camera.h"
#include "Chassis.h"
#include "BallTouch.h"
#include "Kick.h"
#include "Bluetooth.h"
#include "Bottom.h"
#include "Shared.h"

//driveDates index
#define ANGLE       0
#define POWER       1
#define ROTATION    2

class Player
{
public:
    virtual ~Player(){};

    virtual Player *update() = 0;
    virtual void play() = 0;

    virtual bool getsLifted();

    void headstart(); 
    
    virtual bool avoidLine();

    virtual int rateGoal();
    virtual int rateBall();
    virtual void rate() = 0;          //Position bewerten (individuell bestimmen)

    virtual void communicate() = 0; // Daten zwischen Robotern austauschen (individuell welche daten)

protected:
    int _goalRating;
    int _ballRating;
    float _rating;

    int _driveDates[3];
    int _lastDriveDates[3];

    //avoidLine
    bool _sawLine;
    unsigned long _sawTimer;

    byte _setMsg[BT_MSG_SIZE];
};