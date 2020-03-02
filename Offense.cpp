#include "Offense.h"

extern Compass cmps;
extern Ultrasonic us;
extern Pui pui;
extern BallTouch ballTouch;
extern Chassis m;
extern Camera camera;
extern Kick kick;
extern Bluetooth bt;
extern Bottom bottom;

extern Defense defense;
extern Standby standby;

extern bool headstart;
extern unsigned long headstartTimer;

Player *Offense::update()
{
    currentState = State::offense;
    if (_switchToDef)
    {
        LogPlayer("Defense");
        return &defense;
    }
    else if (pui.button_stop)
    {
        LogPlayer("Standby");
        return &standby;
    }
    return this;
}

void Offense::play()
{
    rateBall();
    // rateGoal();

    if (pui.switch_headstart)
        m.headstart();

    else
    {
        if (bottom.seesLine())
        {
            if (us.getLeft() < us.getRight() && (us.getLeft() < us.getFrontLeft() || us.getLeft() < us.getFrontRight()) && us.getLeft() < us.getBack())
                m.drive(270, SPIELGESCHWINDIGKEIT + 10, cmps.getPIDOutput());
            else if (us.getRight() < us.getLeft() && (us.getRight() < us.getFrontLeft() || us.getRight() < us.getFrontRight()) && us.getRight() < us.getBack())
                m.drive(90, SPIELGESCHWINDIGKEIT + 10, cmps.getPIDOutput());
            else if (us.getBack() < us.getLeft() && (us.getBack() < us.getFrontLeft() || us.getBack() < us.getFrontRight()) && us.getBack() < us.getRight())
                m.drive(0, SPIELGESCHWINDIGKEIT + 10, cmps.getPIDOutput());
            else if ((us.getFrontLeft() < us.getLeft() || us.getFrontRight() < us.getLeft()) && (us.getFrontLeft() < us.getRight() || us.getFrontRight() < us.getRight()) && (us.getFrontLeft() < us.getBack() || us.getFrontRight() < us.getBack()))
                m.drive(180, SPIELGESCHWINDIGKEIT + 10, cmps.getPIDOutput());
            else
                m.drive(180, SPIELGESCHWINDIGKEIT + 10, cmps.getPIDOutput());
        }
        else
        {
            if (camera.getBPos() != 0)
                follow();
            else
                search();
        }
    }

    rate();
    communicate();
}

void Offense::search()
{
    m.drive(180, SPIELGESCHWINDIGKEIT, cmps.getPIDOutput());
    // _curveSearch = _lastBallPos < 160 ? _curveSearch - 0.3 : _curveSearch + 0.3;
    // if (abs(_curveSearch) <= 70)
    //     m.drive(180 + _curveSearch, SPIELGESCHWINDIGKEIT - abs(cmps.getPIDOutput()), cmps.getPIDOutput());
    // else
    //     m.drive(180, SPIELGESCHWINDIGKEIT - abs(cmps.getPIDOutput()), cmps.getPIDOutput());
    // _curveFlw = 0;
}

void Offense::follow()
{
    // if (_ballRating > 160)
    // {
    //     m.drive(map(camera.getBPos(), 0, 320, 90, -90), SPIELGESCHWINDIGKEIT + 10 - abs(cmps.getPIDOutput()), cmps.getPIDOutput());
    //     _curveFlw = 0;
    // }
    // else
    // {
    //     if (camera.getBPos() < 160 && camera.getBPos() > 60)
    //         _curveFlw += 1;
    //     else if (camera.getBPos() > 160 && camera.getBPos() < 240)
    //         _curveFlw -= 1;
    //     else if (camera.getBPos() < 60)
    //         _curveFlw += 0.5;
    //     else
    //         _curveFlw -= 0.5;
    //     m.drive(_curveFlw, SPIELGESCHWINDIGKEIT - abs(cmps.getPIDOutput()), cmps.getPIDOutput());
    // }

    // _curveSearch = 0;
    // _lastBallPos = camera.getBPos();
    m.drive(map(camera.getBPos(), 0, 320, 90, -90), SPIELGESCHWINDIGKEIT, cmps.getPIDOutput());
    if (ballTouch.hasBall())
        kick.kick();
}

void Offense::rate()
{
    if (bt.getMessage(BT_INDEX_SWITCH))
    {
        #if RATE_BALL_WEIGHT + RATE_GOAL_WEIGHT == 100
            // _rating = _ballRating * RATE_BALL_WEIGHT / 100 + _goalRating * RATE_GOAL_WEIGHT / 100; would be correct
            _rating = _ballRating;
            // Serial.println(_rating);
            _switchToDef = _rating < 20;
            LogBluetooth("Switch to defense");
        #else
            LogPlayer("Sum of weights doesnt equal 1");
        #endif
    }
    else
        _switchToDef = false;
}

void Offense::communicate()
{
    _setMsg[BT_INDEX_SWITCH] = _switchToDef;

    bt.setMessage(_setMsg);
}