#include "Player.h"

extern Compass cmps;
extern Ultrasonic us;
extern Pui pui;
extern BallTouch ballTouch;
extern Chassis m;
extern Camera camera;
extern Kick kick;
extern Bluetooth bt;

int Player::rateBall()
{
    _ballRating = abs((150 - abs(150 - camera.getBPos())) * 255 / 150);
    return _ballRating;
}


int Player::rateGoal()
{
    _goalRating = camera.getGWidth()/ 30 *255 / 10;
    return _goalRating;
}

void Player::initPID()
{
    _myPID.SetMode(AUTOMATIC);
    // konfiguriere PID-Regler
    _myPID.SetTunings(PID_FILTER_P, PID_FILTER_I, PID_FILTER_D);
    _myPID.SetOutputLimits(-255, 255);
}

void Player::updatePID()
{
    _input = -((cmps.getAngle() + 180) % 360 - 180);
    _myPID.Compute();
}

int Player::getPIDOutput()
{
    return _output;
}

bool Player::getsLifted()
{
    if(cmps.getPitch() < 252 && cmps.getPitch() > 200)
        return true;
    return false;
}
