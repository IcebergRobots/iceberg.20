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
    updatePID();
    rateGoal();
    rateBall();
    // defGoal();
    m.brake(false);
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
    // m.drive(180,30 - getPIDOutput(), getPIDOutput());
    if (!_defDir)
    {
        m.drive(270, 40 - getPIDOutput(), getPIDOutput());
        if (us.getRight() < 40)
            _defDir = true;
    }
    else
    {
        m.drive(90, 40 - getPIDOutput(), getPIDOutput());
        if (us.getLeft() < 40)
            _defDir = false;
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
    _maybeSwitchToOff = _rating > 180;
#elif
    LogPlayer("Sum of weights doesnt equal 100%");
#endif
}

void Defense::communicate()
{
    Serial.println(_maybeSwitchToOff);
    _setMsg[BT_INDEX_SWITCH] = _maybeSwitchToOff;
    bt.setMessage(_setMsg);
}