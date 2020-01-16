#pragma once

#include <Wire.h>

class Hardware {
    public:
        virtual void init() = 0;
        virtual void update() = 0;
};