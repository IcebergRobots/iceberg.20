#pragma once

#include "Player.h"
#include "Offense.h"

class Defense : public Player
{
public:
    Defense()
        : _lastTime(millis()) {};

    Player *update() override;
    void play() override;

    void defGoal();

private:
    unsigned long _lastTime;
};