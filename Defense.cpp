#include "Defense.h"

extern Compass cmps;
extern Ultrasonic us;
extern PUI pui;
extern BallTouch ballTouch;
extern Chassis m;
extern Camera camera;
extern Kick kick;

extern Offense offense;

void Defense::play()
{
    defGoal();
}

Player *Defense::update()
{
    if (camera.getBPos() != 0)
    {
        Serial.println("Offense");
        return &offense;
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