#include "Standby.h"

extern Compass cmps;
extern Ultrasonic us;
extern Pui pui;
extern BallTouch ballTouch;
extern Chassis m;
extern Camera camera;
extern Kick kick;

extern Defense defense;
extern Offense offense;

Player* Standby::update()
{
    if(!getsLifted()){
        m.setMotEn(true);
        ballTouch.setEn(true);
        us.setEn(true);
        Serial.println("Offense");
        return &offense;
    }
    return this;
}

void Standby::play()
{
    m.brake(false);
    m.setMotEn(false);
    ballTouch.setEn(false);
    us.setEn(false);
}

void Standby::rate()
{

}

void Standby::communication()
{

}