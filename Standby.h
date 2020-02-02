#pragma once

#include "Player.h"

class Standby : public Player
{
public:
    Player* update() override;
    void play() override;
};