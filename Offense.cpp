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

    if (camera.getBPos() != 0)
        follow();
    else
        search();
    
    rate();
    communicate();
}

void Offense::search()
{
    _curveSearch = _lastBallPos < 160 ? _curveSearch - 0.4 : _curveSearch + 0.4;
    m.drive(180 + _curveSearch, 60, updatePID());

    _curveFlw = 0;
}

void Offense::follow()
{
    if(rateBall() > 170)
    {
        m.drive(map(camera.getBPos(), 0, 320, 90, -90), 60, updatePID()); 
        _curveFlw = 0;
    }
    else
    {
        if(camera.getBPos() < 160 && camera.getBPos() > 80)
            _curveFlw += 0.6;
        else if(camera.getBPos() > 160 && camera.getBPos() < 240)
            _curveFlw -= 0.6;
        else if(camera.getBPos() < 80)
            _curveFlw += 0.3;
        else
            _curveFlw -= 0.3;
        m.drive(_curveFlw, 60, updatePID());
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
            _rating = _ballRating * RATE_BALL_WEIGHT + _goalRating * RATE_GOAL_WEIGHT;
            _switchToDef = _rating < 50;
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