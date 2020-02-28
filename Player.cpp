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

bool Player::getsLifted()
{
    if(cmps.getPitch() < 252 && cmps.getPitch() > 200)
        return true;
    return false;
}
