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

    _driveDates[POWER] = SPIELGESCHWINDIGKEIT;
    _driveDates[ROTATION] = cmps.getPIDOutput();

    if (!avoidLine())
    {
        defGoal();
    }

    m.drive(_driveDates[ANGLE], _driveDates[POWER], _driveDates[ROTATION]);
    for (int i = 0; i < 3; i++)
        _lastDriveDates[i] = _driveDates[i];

    rate();
    communicate();
}

Player *Defense::update()
{
   currentState = STATE_DEFENSE;
    if (_switchToOff)
    // if (!camera.getBPos() && false)
    {
        LogPlayer("Offense");
        return &offense;
    }
    if (pui.button_stop || getsLifted())
    {
        LogPlayer("Standby");
        return &standby;
    }
    return this;
}

void Defense::defGoal()
{
  
    if (us.getBack() < 6)
    {
        _driveDates[ANGLE] = 0;
    }
    else if (us.getBack() > 30 && us.getRight() > 40) //&& us.getLeft() > 35
    {
        _driveDates[ANGLE] = 180;
    }
    else
    {

        if (_defDir)
        {
            _driveDates[ANGLE] = 90;
            if (us.getLeft() < 50 && millis() - _defDirTimer > 1000)
            {
                _defDirTimer = millis();
                _defDir = false;
            }
        }
        else
        {
            _driveDates[ANGLE] = 270;
            if (us.getRight() < 50 && millis() - _defDirTimer > 1000)
            {
                _defDirTimer = millis();
                _defDir = true;
            }
        }
    }
}

void Defense::rate()
{
    if (_maybeSwitchToOff)
    {
        LogBluetooth("Offense");
        _switchToOff = bt.getMessage(BT_INDEX_SWITCH);
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
    _setMsg[BT_INDEX_CURRENTSTATE] = currentState;
    bt.setMessage(_setMsg);
}
