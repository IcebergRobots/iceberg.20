#include "Defense.h"

extern Compass cmps;
extern Ultrasonic us;
extern Pui pui;
extern BallTouch ballTouch;
extern Chassis m;
extern Camera camera;
extern Kick kick;

extern Offense offense;
extern Standby standby;

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
    m.drive(180,70);
    // if(us.getBack() < 10)
    // {
    //     m.drive(0,40);
    // }else if(us.getBack() > 20)
    // {
    //     m.drive(180,40);
    // }else{
    //     if(_defDir == 0) {
    //         m.drive(270, 40);
    //         if(us.getRight() < 65) _defDir = 1;
    //     }else if(_defDir == 1)
    //     {
    //         m.drive(90, 40);
    //         if(us.getLeft() < 65) _defDir = 0;
    //     }
    // }

}

void Defense::rate()
{

}

void Defense::communication()
{
    
}