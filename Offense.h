#pragma once

#include "Player.h"
#include "Defense.h"

class Offense : public Player
{
public:
    Offense()
        : _lastTime(millis()) {};

    Player *update() override;
    void play() override;

    void follow();
    void search();

private:
    unsigned long _lastTime;
};