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
    m.brake(false);
    m.setMotEn(false);
    ballTouch.setEn(false);
    us.setEn(false);
}

Player* Standby::update()
{
    if(!getsLifted() && bt.b == 'o'){
        m.setMotEn(true);
        ballTouch.setEn(true);
        us.setEn(true);
        Serial.println("Offense");
        return &offense;
    } else if(bt.b == 'd')
    {
        m.setMotEn(true);
        ballTouch.setEn(true);
        us.setEn(true);
        Serial.println("Defense");
        return &defense; 
    }
    return this;
}

void Standby::rate()
{

}

void Standby::communication()
{

}