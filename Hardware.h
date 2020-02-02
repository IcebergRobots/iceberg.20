#pragma once

#include <Wire.h>
#include <SPI.h>

class Hardware {
    public:
        virtual void init() = 0;
        virtual void update() = 0;

        void setEn(const bool& enabled);
        const bool getEn();
    protected:
        bool _enabled;
};