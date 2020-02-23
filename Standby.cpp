#include "Standby.h"

extern Compass cmps;
extern Ultrasonic us;
extern Pui pui;
extern BallTouch ballTouch;
extern Chassis m;
extern Camera camera;
extern Kick kick;
extern Bluetooth bt;

extern Defense defense;
extern Offense offense;

void Standby::play()
{
    if(_disOnce)
    {
        _disOnce = false;
        m.setMotEn(false);
        ballTouch.setEn(false);
        us.setEn(false);
    }
}

Player* Standby::update()
{
    currentState = State::standby;
    if(!getsLifted()){
        _disOnce = true;
        m.setMotEn(true);
        ballTouch.setEn(true);
        us.setEn(true);
        LogPlayer("Offense");
        return &offense;
    }
    return this;
}

void Standby::rate()
{

}

void Standby::communication()
{

}