#include "Offense.h"

extern Compass cmps;
extern Ultrasonic us;
extern Pui pui;
extern BallTouch ballTouch;
extern Chassis m;
extern Camera camera;
extern Kick kick;
extern Bluetooth bt;

extern Defense defense;
extern Standby standby;

void Offense::search()
{
    m.drive(180, 30);
}

void Offense::follow()
{
    m.drive(map(camera.getBPos(), 0, 320, 90, -90), 30, 0); 
    if (ballTouch.hasBall())
    {
        kick.kick();
    }
}

void Offense::play()
{
    if (camera.getBPos() != 0)
        follow();
    else
        search();
}

Player *Offense::update()
{
    currentState = State::offense;
    if (camera.getBPos() == 0 && us.getFrontLeft() < 10)
    {
        LogPlayer("Defense");
        return &defense;
    }else if(getsLifted()){
        LogPlayer("Standby");
        return &standby;
    }
    return this;
}

void Offense::rate()
{

}

void Offense::communication()
{
    
}