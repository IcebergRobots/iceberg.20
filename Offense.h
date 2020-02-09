#pragma once

#include "Player.h"
#include "Defense.h"
#include "Standby.h"

class Offense : public Player
{
public:
    Player *update() override;
    void play() override;

    void rate() override;
    void communication() override;

    void follow();
    void search();

private:
};