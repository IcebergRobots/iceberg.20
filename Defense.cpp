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
    // rateBall();
    // rateGoal();
    // defGoal();
    rate();
    communicate();
}

Player *Defense::update()
{
    currentState = State::defense;
    if (_switchToOff)
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
    m.drive(180,30, updatePID());
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
    if(_maybeSwitchToOff)
    {
        LogBluetooth("Offense");
        _switchToOff = bt.getMessage(BT_INDEX_SWITCH);
    }else
        _switchToOff = false;

    #if RATE_BALL_WEIGHT + RATE_GOAL_WEIGHT == 100
        _rating = _ballRating * RATE_BALL_WEIGHT/100 + _goalRating * RATE_GOAL_WEIGHT/100;
        _maybeSwitchToOff = _rating > 170;
    #elif
        LogPlayer("Sum of weights doesnt equal 100%");
    #endif
}

void Defense::communicate()
{
    _setMsg[BT_INDEX_SWITCH] = _maybeSwitchToOff;
    bt.setMessage(_setMsg);
}