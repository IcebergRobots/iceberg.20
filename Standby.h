#pragma once

#include "Player.h"
#include "Offense.h"
#include "Defense.h"

class Standby : public Player
{
public:
    Player* update() override;
    void play() override;

    void rate() override;
    void communicate() override;
private:
    bool _disOnce = true;
};