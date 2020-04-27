#pragma once

#include "Player.h"
#include "Offense.h"
#include "Standby.h"

class Defense : public Player
{
public:
    Player *update() override;
    void play() override;

    void rate() override;
    void communicate() override;

    void defGoal();

private:
    bool _maybeSwitchToOff;
    bool _switchToOff;

    //def goal
    bool _defDir;
    unsigned long _defDirTimer;
};