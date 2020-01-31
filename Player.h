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
    void init();
    void update();

private:
    bool offens;
    bool defense;
    bool rdyToSwitch;

};