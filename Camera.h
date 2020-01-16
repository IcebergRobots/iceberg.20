#pragma once

#include "Config.h"
#include "Hardware.h"

#include <Pixy.h>


class Camera : private Pixy, public Hardware
{
public: 
    Camera();

    void init() override;
    void update() override;

    bool isEnabled();

    int getBArea();
    int getBPos();

private:
    int blockCount = 0;
    int ballCount = 0;
    int goalCount = 0;

    int ballArea = 0;
    int ballPos = 0;
    int goalArea = 0;
    int goalPos = 0;
    unsigned long timer = 0;
    
};


