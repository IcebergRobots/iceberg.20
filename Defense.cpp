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
    if (camera.getBPos() != 0 && false)
    {
        Serial.println("Offense");
        return &offense;
    }
    else
    {
        return this;
    }
    return this;
}

void Defense::defGoal()
{
    rate();
    //m.drive(180,70);
    // if(us.getBack() < 15)
    // {
    //     m.drive(0,40);
    // }else if(us.getBack() > 60)
    // {
    //     m.drive(180,40);
    // }else{
        // if(_defDir == 0) {
        //     m.drive(270, 20);
        //     if(us.getRight() < 50) _defDir = 1;
        // }else if(_defDir == 1)
        // {
        //     m.drive(90, 20);
        //     if(us.getLeft() < 50) _defDir = 0;
        // }
    // }

}

void Defense::rate()
{
    _camRating = (camera.getGWidth()*255 / 30);
    _ballRating = abs((150 - abs(150 - camera.getBPos())) * 255 / 150);
    Serial.println(_camRating);
}

void Defense::communication()
{
    
}