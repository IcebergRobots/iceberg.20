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
#include "PID_v1.h"
#include "Bluetooth.h"

class Player
{
public:
    virtual ~Player(){};

    virtual Player *update() = 0;
    virtual void play() = 0;

    virtual void initPID();
    virtual int updatePID(); 
    virtual void updatePos();//Kompass ausrichten

    bool getsLifted();
    
    virtual int rateGoal();
    virtual int rateBall();
    virtual void rate() = 0;          //Position bewerten (individuell bestimmen)

    virtual void communication() = 0; // Daten zwischen Robotern austauschen (individuell welche daten)

    enum class State {
        standby = 0, offense = 1, defense = 2 
    };
    State currentState;
private:
    double _setpoint = 0;    //PID Zielwert
    double _input, _output;          //CMPS Input, rotationsstärke
    PID _myPID = PID(&_input, &_output, &_setpoint, PID_FILTER_P, PID_FILTER_I, PID_FILTER_D, DIRECT);

protected:
    int _goalRating;
    int _ballRating;
    int _rating;

};