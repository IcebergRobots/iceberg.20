#include "Defense.h"

extern Compass cmps;
extern Ultrasonic us;
extern Pui pui;
extern BallTouch ballTouch;
extern Chassis m;
extern Camera camera;
extern Kick kick;
extern Bluetooth bt;

extern Offense offense;
extern Standby standby;

void Defense::play()
{
    defGoal();
}

Player *Defense::update()
{
    if (camera.getBPos() != 0 && rateBall() > 170)
    {
        LogPlayer("Offense");
        return &offense;
    } if(getsLifted()){
        LogPlayer("Standby");
        return &standby;
    }
    return this;
}

void Defense::defGoal()
{
    m.drive(180,30, 30);
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

void Defense::rate() {

}

void Defense::communication()
{
    
}