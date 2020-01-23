#pragma once

#include <Wire.h>
#include <SPI.h>

class Hardware {
    public:
        virtual void init();
        virtual void update();

        void setEn(const bool& enabled);
        const bool getEn();
    protected:
        bool _enabled;
};