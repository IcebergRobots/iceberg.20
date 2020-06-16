#include "Standby.h"

extern Compass cmps;
extern Ultrasonic us;
extern Pui pui;
extern BallTouch ballTouch;
extern Chassis m;
extern Camera camera;
extern Kick kick;
extern Bluetooth bt;
extern Bottom bottom;

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
        bottom.setEn(false);
    }

    if(pui.button_compass)
        cmps.cali();

    if(pui.button_lightBarrierCalibration)
    {
        ballTouch.setEn(true);
        ballTouch.calibrate();
        ballTouch.setEn(false);
    }

    if(pui.button_kick)
    {
        if(kick.getEn())
            kick.kick();
        else
        {
            kick.setEn(true);
            kick.kick();
            kick.setEn(false);
        }
    }

    // if(!cmps.calibrated)
    //     cmps.checkCalibration();
}

Player* Standby::update()
{
    currentState = STATE_STANDBY;
    if(pui.button_start || bt.getMessage(BT_INDEX_CURRENTSTATE) != STATE_STANDBY){
        _disOnce = true;
        m.setMotEn(ENDISABLE_CHASSIS);
        ballTouch.setEn(ENDISABLE_BALLTOUCH);
        us.setEn(ENDISABLE_ULTRASONIC);
        bottom.setEn(ENDISABLE_BOTTOM);

        enHeadstart = pui.switch_headstart;
        headstartTimer = millis();
//        if(chooseRobot() == 1)
//        {
//            LogPlayer("Defense");
//            return &defense;
//        }
//        else
//        {
//            LogPlayer("Offense");
//            return &offense;
//        }
          return &defense;
    }
    return this;
}

void Standby::rate()
{

}

void Standby::communicate()
{
    
}
