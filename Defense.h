#pragma once

#include "Player.h"
#include "Offense.h"

class Defense : public Player
{
public:
    Player *update() override;
    void play() override;

    void defGoal();

private:
};