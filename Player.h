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

class Player
{
public:
    virtual ~Player(){};

    virtual Player *update() = 0;
    virtual void play() = 0;

    bool getsLifted();
    
    virtual int rateGoal();
    virtual int rateBall();
    virtual void rate() = 0;          //Position bewerten (individuell bestimmen)

    virtual void communicate() = 0; // Daten zwischen Robotern austauschen (individuell welche daten)

    enum class State {
        standby = 0, offense = 1, defense = 2 
    };
    State currentState;
private:

protected:
    int _goalRating;
    int _ballRating;
    float _rating;

    byte _setMsg[BT_MSG_SIZE];
};