#include "Player.h"

extern Compass cmps;
extern Ultrasonic us;
extern Pui pui;
extern BallTouch ballTouch;
extern Chassis m;
extern Camera camera;
extern Kick kick;
extern Bluetooth bt;
extern Bottom bottom;

extern Shared shared;

int Player::rateBall()
{
    _ballRating = abs((150 - abs(150 - camera.getBPos())) * 255 / 150);
    return _ballRating;
}

void Player::headstart()
{
    Serial.println("yo");
    if (millis() - shared.headstartTimer <= 500)
    {
        Serial.println("headstart");
        // for (int i = 0; i < 4; i++)
        // {
        //   motors[i].setPower(255);
        //   motors[i].steerMotor();
        // }
        _driveDates[ANGLE] = 0;
        _driveDates[POWER] = 255;
    }
    else
        shared.enHeadstart = false;
}

bool Player::avoidLine()
{
    if (bottom.seesLine())
    {
        _sawLine = true;
        _sawTimer = millis();
    }
    else
    {
        if (_sawLine)
        {
            if (millis() - _sawTimer >= 1000) _sawLine = false;
            if(us.getLeft() != 9)
            {
            if (us.getLeft() < us.getRight() && (us.getLeft() < us.getFrontLeft() || us.getLeft() < us.getFrontRight()) && us.getLeft() < us.getBack() && us.getLeft() < 20)
                _driveDates[ANGLE] = 270;
            else if (us.getRight() < us.getLeft() && (us.getRight() < us.getFrontLeft() || us.getRight() < us.getFrontRight()) && us.getRight() < us.getBack() && us.getRight() < 20)
                _driveDates[ANGLE] = 90;
            else if (us.getBack() < us.getLeft() && (us.getBack() < us.getFrontLeft() || us.getBack() < us.getFrontRight()) && us.getBack() < us.getRight() && us.getBack() < 20)
                _driveDates[ANGLE] = 0;
            else if ((us.getFrontLeft() < us.getLeft() || us.getFrontRight() < us.getLeft()) && (us.getFrontLeft() < us.getRight() || us.getFrontRight() < us.getRight()) && (us.getFrontLeft() < us.getBack() || us.getFrontRight() < us.getBack()) && (us.getFrontLeft() < 20 || us.getFrontRight() < 20))
                _driveDates[ANGLE] = 180;
            else
                return false;
            return true;
            }else
            {
              if ((us.getRight() < us.getFrontLeft() || us.getRight() < us.getFrontRight()) && us.getRight() < us.getBack() && us.getRight() < 20)
                _driveDates[ANGLE] = 90;
            else if ((us.getBack() < us.getFrontLeft() || us.getBack() < us.getFrontRight()) && us.getBack() < us.getRight() && us.getBack() < 20)
                _driveDates[ANGLE] = 0;
            else if ((us.getFrontLeft() < us.getRight() || us.getFrontRight() < us.getRight()) && (us.getFrontLeft() < us.getBack() || us.getFrontRight() < us.getBack()) && (us.getFrontLeft() < 20 || us.getFrontRight() < 20))
                _driveDates[ANGLE] = 180;
            else
                return false;
            return true;
            }
            
        }
    }
    return false;
}

int Player::rateGoal()
{
    _goalRating = camera.getGWidth() / 30 * 255 / 10;
    return _goalRating;
}

bool Player::getsLifted()
{
    // if (cmps.getPitch() > 15 && cmps.getPitch() < 35)
    //     return true;
    return false;
}
