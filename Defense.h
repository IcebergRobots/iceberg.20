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
    int _defTimer;
    bool _defDir;
    bool _maybeSwitchToOff;
    bool _switchToOff;
};