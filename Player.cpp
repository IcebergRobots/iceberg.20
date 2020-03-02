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

int Player::rateBall()
{
    _ballRating = abs((150 - abs(150 - camera.getBPos())) * 255 / 150);
    return _ballRating;
}

// void Player::avoidLine()
// {
//     switch (bottom.getAngel())
//     {
//     case 90:
//         m.drive(270, SPIELGESCHWINDIGKEIT - abs(cmps.getPIDOutput()), cmps.getPIDOutput());
//         break;
//     case 270:
//         m.drive(90, SPIELGESCHWINDIGKEIT - abs(cmps.getPIDOutput()), cmps.getPIDOutput());
//         break;
//     case 180:
//         m.drive(0, SPIELGESCHWINDIGKEIT - abs(cmps.getPIDOutput()), cmps.getPIDOutput());
//         break;
//     default:
//         break;
//     }
// }

// bool Player::checkBounds()
// {
//     if (millis() - _checkTimer >= 500)
//     {
//         if (us.getLeft() < 50)
//         {
//             m.drive(270, SPIELGESCHWINDIGKEIT - abs(cmps.getPIDOutput()), cmps.getPIDOutput());
//             _checkTimer = millis();
//             return false;
//         }
//         else if (us.getRight() < 50)
//         {
//             m.drive(90, SPIELGESCHWINDIGKEIT - abs(cmps.getPIDOutput()), cmps.getPIDOutput());
//             _checkTimer = millis();
//             return false;
//         }
//         else if (us.getFront() < 50)
//         {
//             m.drive(180, SPIELGESCHWINDIGKEIT - abs(cmps.getPIDOutput()), cmps.getPIDOutput());
//             _checkTimer = millis();
//             return false;
//         } else
//             return true;
//     }
//     else
//     {
//         //Check Boden
//         return true;
//     }
// }

int Player::rateGoal()
{
    _goalRating = camera.getGWidth() / 30 * 255 / 10;
    return _goalRating;
}

bool Player::getsLifted()
{
    if (cmps.getPitch() > 15 && cmps.getPitch() < 35)
        return true;
    return false;
    return false;
}
