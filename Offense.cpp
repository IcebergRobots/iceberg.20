#include "Offense.h"

extern Compass cmps;
extern Ultrasonic us;
extern PUI pui;
extern BallTouch ballTouch;
extern Chassis m;
extern Camera camera;
extern Kick kick;

extern Defense defense;

void Offense::search()
{
    m.drive(0, -30, 0);
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
    if (camera.getBPos() == 0)
        search();
    else
        follow();
}

Player *Offense::update()
{
    if (camera.getBPos() == 0 && us.getFrontLeft() < 10)
    {
        Serial.println("Defense");
        return &defense;
    }
    else
    {
        return this;
    }
}