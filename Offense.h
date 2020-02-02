#pragma once

#include "Player.h"
#include "Defense.h"

class Offense : public Player
{
public:
    Player *update() override;
    void play() override;

    void follow();
    void search();

private:
};