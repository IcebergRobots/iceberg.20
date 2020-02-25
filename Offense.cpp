#include "Offense.h"

extern Compass cmps;
extern Ultrasonic us;
extern Pui pui;
extern BallTouch ballTouch;
extern Chassis m;
extern Camera camera;
extern Kick kick;
extern Bluetooth bt;

extern Defense defense;
extern Standby standby;

Player *Offense::update()
{
    currentState = State::offense;
    if (_switchToDef)
    {
        LogPlayer("Defense");
        return &defense;
    }else if(getsLifted()){
        LogPlayer("Standby");
        return &standby;
    }
    return this;
}

void Offense::play()
{
    rateBall();
    rateGoal();

    if (camera.getBPos() != 0 && _goalRating < 230)
        follow();
    else if(_goalRating > 230)
        m.drive(180,SPIELGESCHWINDIGKEIT - abs(getPIDOutput()), getPIDOutput());
    else
        search();
    // m.drive(0,100);
     rate();
    communicate();
}

void Offense::search()
{
    _curveSearch = _lastBallPos < 160 ? _curveSearch - 0.3 : _curveSearch + 0.3;
    if(abs(_curveSearch) <= 70)
        m.drive(180 + _curveSearch, SPIELGESCHWINDIGKEIT - abs(getPIDOutput()), getPIDOutput());
    else
        m.drive(180, SPIELGESCHWINDIGKEIT - abs(getPIDOutput()), getPIDOutput());
    _curveFlw = 0;
}

void Offense::follow()
{
    if(_ballRating > 180)
    {
        m.drive(map(camera.getBPos(), 0, 320, 90, -90), SPIELGESCHWINDIGKEIT + 10 - abs(getPIDOutput()), getPIDOutput()); 
        _curveFlw = 0;
    }
    else
    {
        if(camera.getBPos() < 160 && camera.getBPos() > 60)
            _curveFlw += 1;
        else if(camera.getBPos() > 160 && camera.getBPos() < 240)
            _curveFlw -= 1;
        else if(camera.getBPos() < 60)
            _curveFlw += 0.5;
        else
            _curveFlw -= 0.5;
        m.drive(_curveFlw, SPIELGESCHWINDIGKEIT - abs(getPIDOutput()), getPIDOutput());
    }

    if (ballTouch.hasBall())
        kick.kick();

    _curveSearch = 0;
    _lastBallPos = camera.getBPos();
}



void Offense::rate()
{
    if(bt.getMessage(BT_INDEX_SWITCH))
    {
        LogBluetooth("Switch to defense");
        #if RATE_BALL_WEIGHT + RATE_GOAL_WEIGHT == 100
            _rating = _ballRating * RATE_BALL_WEIGHT / 100 + _goalRating * RATE_GOAL_WEIGHT / 100;
            // Serial.println(_rating);
            _switchToDef = _rating < 100;
        #else
            LogPlayer("Sum of weights doesnt equal 1");
        #endif
    }else
        _switchToDef = false;
}

void Offense::communicate()
{
    _setMsg[BT_INDEX_SWITCH] = _switchToDef;

    bt.setMessage(_setMsg);
}