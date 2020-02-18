#include "Player.h"

extern Compass cmps;
extern Ultrasonic us;
extern Pui pui;
extern BallTouch ballTouch;
extern Chassis m;
extern Camera camera;
extern Kick kick;
extern Bluetooth bt;

void Player::rateBall()
{
    _ballRating = abs((150 - abs(150 - camera.getBPos())) * 255 / 150);
}


void Player::rateGoal()
{
    _goalRating = (camera.getGWidth()*255 / 30);
}

void Player::updPos()
{
    
}

bool Player::getsLifted()
{
    if(cmps.getPitch() < 255 && cmps.getPitch() > 200)
        return true;
    return false;
}
