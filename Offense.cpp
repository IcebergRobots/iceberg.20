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

extern Shared shared;

Player *Offense::update()
{
    shared.currentState = shared.offense;
    if (_switchToDef)
    {
        LogPlayer("Defense");
        return &defense;
    }
    else if (pui.button_stop || getsLifted())
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

    _driveDates[POWER] = SPIELGESCHWINDIGKEIT;
    _driveDates[ROTATION] = cmps.getPIDOutput();

    if (shared.enHeadstart)
        headstart();
    else
    {
//        if (millis() - _lastTimeSawLine >= 400)
//        {
//            if (_stillSees)
//            {
//                if (us.getLeft() < us.getRight() && (us.getLeft() < us.getFrontLeft() || us.getLeft() < us.getFrontRight()) && us.getLeft() < us.getBack())
//                    _driveDates[ANGLE] = 270;
//                else if (us.getRight() < us.getLeft() && (us.getRight() < us.getFrontLeft() || us.getRight() < us.getFrontRight()) && us.getRight() < us.getBack())
//                    _driveDates[ANGLE] = 90;
//                // else if (us.getBack() < us.getLeft() && (us.getBack() < us.getFrontLeft() || us.getBack() < us.getFrontRight()) && us.getBack() < us.getRight())
//                //     _driveDates[ANGLE] = 0;
//                // else if ((us.getFrontLeft() < us.getLeft() || us.getFrontRight() < us.getLeft()) && (us.getFrontLeft() < us.getRight() || us.getFrontRight() < us.getRight()) && (us.getFrontLeft() < us.getBack() || us.getFrontRight() < us.getBack()))
//                //     _driveDates[ANGLE] = 180;
//                else if (us.getBack() < us.getLeft() && (us.getBack() < us.getFrontLeft() || us.getBack() < us.getFrontRight()) && us.getBack() < us.getRight() || (us.getFrontLeft() < us.getLeft() || us.getFrontRight() < us.getLeft()) && (us.getFrontLeft() < us.getRight() || us.getFrontRight() < us.getRight()) && (us.getFrontLeft() < us.getBack() || us.getFrontRight() < us.getBack()))
//                {
//                    if (us.getLeft() < us.getRight())
//                        _driveDates[ANGLE] = 270;
//                    else
//                        _driveDates[ANGLE] = 90;
//                }
//                else
//                    _driveDates[ANGLE] = 180;
//                
//                if(!bottom.seesLine() && millis() - _stillSeesTimer >= 800)
//                {
//                    _stillSees = false;
//                    _stillSeesTimer = millis();
//                }
//            }
//            else
//            {
//                if (bottom.seesLine())
//                {
//                    _lastTimeSawLine = millis();
//                    if(us.getLeft() + us.getRight() < 45 && us.getLeft() != 9)
//                    {
//                        _driveDates[ANGLE] = 180;
//                        Serial.println("Crazy");
//                    }else
//                    _driveDates[ANGLE] = _lastDriveDates[ANGLE] + 180;
//                    // avoidLine();
//                }
//                else
//                {
//                    if (camera.getBPos() != 0)
//                        follow();
//                    else
//                        search();
//                }
//            }
//        }
//        else
//        {
//            _driveDates[ANGLE] = _lastDriveDates[ANGLE];
//            LogPlayer("Drive other: " + _driveDates[ANGLE]);
//            if (bottom.seesLine())
//                _stillSees = true;
//            else
//                _stillSees = false;
//        }
      if(!avoidLine())
        {
          if (camera.getBPos() != 0)
                        follow();
                    else
                        search();
        }
    }

    m.drive(_driveDates[ANGLE], _driveDates[POWER], _driveDates[ROTATION]);
    for (int i = 0; i < 3; i++)
        _lastDriveDates[i] = _driveDates[i];

    rate();
    communicate();
}

void Offense::search()
{
    _driveDates[ANGLE] = 180;
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
    _driveDates[ANGLE] = map(camera.getBPos(), 0, 320, 90, -90);
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
    _setMsg[BT_INDEX_CURRENTSTATE] = shared.currentState;   //0 = standby, 1 = offense, 2 = defense
    bt.setMessage(_setMsg);
}
