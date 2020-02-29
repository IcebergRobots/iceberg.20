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
    void communicate() override;

    void follow();
    void search();

private:
    //Searchlogic
    int _lastBallPos;
    float _curveSearch;
    float _curveFlw;

    unsigned long _offTimer;

    //rating
    bool _switchToDef;
};