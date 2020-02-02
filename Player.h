#pragma once

#include "Config.h"
#include "Display.h"
#include "Ultrasonic.h"
#include "Compass.h"
#include "Utility.h"
#include "PUI.h"
#include "Camera.h"

class Player
{
public:
    Player();

    virtual ~Player(){};

    virtual Player *update() = 0;
    virtual void play() = 0;

private:
};