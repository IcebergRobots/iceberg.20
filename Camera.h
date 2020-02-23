#pragma once

#include "Config.h"
#include "Hardware.h"

#include <Pixy.h>

#define SIG_BALL 1
#define SIG_GOAL 2

class Camera : private Pixy, public Hardware
{
public: 
    Camera(const bool& enabled = false)
        {
            _enabled = enabled;
        };

    void init() override;
    void update() override;

    int getBArea();
    int getBPos();

    int getGArea();
    int getGWidth();


private:
    int _blockCount;
    int _ballCount;
    int _goalCount;

    int _ballHeight;
    int _ballWidth;
    int _ballArea;
    int _ballPos;

    int _goalHeight;
    int _goalWidth;
    int _goalArea;
    int _goalPos;
    unsigned long _timer;
    
};


