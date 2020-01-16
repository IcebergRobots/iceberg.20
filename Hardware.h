#pragma once

#include <Wire.h>
#include <SPI.h>

class Hardware {
    public:
        virtual void init() = 0;
        virtual void update() = 0;
};