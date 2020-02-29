#include "Defense.h"

extern Compass cmps;
extern Ultrasonic us;
extern Pui pui;
extern BallTouch ballTouch;
extern Chassis m;
extern Camera camera;
extern Kick kick;
extern Bluetooth bt;

extern Offense offense;
extern Standby standby;


void Defense::play()
{
    rateGoal();
    rateBall();
    defGoal();
    // m.drive(0,0,cmps.getPIDOutput());

    rate();
    communicate();
}

Player *Defense::update()
{
    currentState = State::defense;
    if (_switchToOff)
    // if (!camera.getBPos() && false)
    {
        LogPlayer("Offense");
        return &offense;
    }
    if (getsLifted() || pui.button_stop)
    {
        LogPlayer("Standby");
        return &standby;
    }
    return this;
}

void Defense::defGoal()
{
    if (!_defDir)
    {
            if(us.getBack() < 10)
                m.drive(0,SPIELGESCHWINDIGKEIT  - abs(cmps.getPIDOutput()), cmps.getPIDOutput());
            else if(us.getBack() > 40)
                m.drive(180,SPIELGESCHWINDIGKEIT  - abs(cmps.getPIDOutput()), cmps.getPIDOutput());
            else
                m.drive(270, SPIELGESCHWINDIGKEIT - abs(cmps.getPIDOutput()), cmps.getPIDOutput());
        if (us.getRight() < 60 && millis() - _defTimer >= 1000 || millis() - _defTimer >= 2000)
        {
            _defTimer = millis();
            _defDir = true;
        }
    }
    else
    {
            if(us.getBack() < 10)
                m.drive(0,SPIELGESCHWINDIGKEIT  - abs(cmps.getPIDOutput()), cmps.getPIDOutput());
            else if(us.getBack() > 55)
                m.drive(180,SPIELGESCHWINDIGKEIT  - abs(cmps.getPIDOutput()), cmps.getPIDOutput());
            else
                m.drive(90, SPIELGESCHWINDIGKEIT - abs(cmps.getPIDOutput()), cmps.getPIDOutput());
        if (us.getLeft() < 60 && millis() - _defTimer >= 1000 || millis() - _defTimer >= 2000)
        {
            _defTimer = millis();
            _defDir = false;
        }
    }
}

void Defense::rate()
{
    if (_maybeSwitchToOff)
    {
        LogBluetooth("Offense");
        _switchToOff = bt.getMessage(BT_INDEX_SWITCH);
        // Serial.println(_switchToOff);
    }
    else
        _switchToOff = false;

    #if RATE_BALL_WEIGHT + RATE_GOAL_WEIGHT == 100
        // _rating = (_ballRating * RATE_BALL_WEIGHT / 100) + (_goalRating * RATE_GOAL_WEIGHT / 100); this would be correct but getGoalWidth doesnt work properly
        _rating = _ballRating;
        _maybeSwitchToOff = _rating > 160;
    #elif
        LogPlayer("Sum of weights doesnt equal 100%");
    #endif
}

void Defense::communicate()
{
    _setMsg[BT_INDEX_SWITCH] = _maybeSwitchToOff;
    bt.setMessage(_setMsg);
}