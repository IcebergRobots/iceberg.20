#include "Defense.h"

extern Compass cmps;
extern Ultrasonic us;
extern PUI pui;
extern BallTouch ballTouch;
extern Chassis m;
extern Camera camera;
extern Kick kick;

void Defense::play()
{
    defGoal();
}

Player *Defense::update()
{
    if (millis() - _lastTime > 3000)
    {
        _lastTime = millis();
        delete this;
        return new Offense;
    }
    else
    {
        return this;
    }
}

void Defense::defGoal()
{
    m.drive(180, 60, 0);
}