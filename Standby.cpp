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

    if(pui.button_compass)
        cmps.cali();

    if(pui.button_lightBarrierCalibration)
    {
        ballTouch.setEn(true);
        ballTouch.calibrate();
        ballTouch.setEn(false);
    }

    if(!cmps.calibrated)
        cmps.checkCalibration();
}

Player* Standby::update()
{
    currentState = State::standby;
    if(!getsLifted() && pui.button_start){
        _disOnce = true;
        m.setMotEn(true);
        ballTouch.setEn(true);
        us.setEn(true);
        LogPlayer("Offense");
        return &offense;

        // switch(lastState)
        // {
        //     case State::offense:
        //         lastState = State::standby;
        //         LogPlayer("Offense");
        //         return &offense;
        //         break;
        //     case State::defense:
        //         lastState = State::standby;
                // LogPlayer("Defense");
                // return &defense;
        //         break;
        // }
    }
    return this;
}

void Standby::rate()
{

}

void Standby::communicate()
{

}