#pragma once

#include "Config.h"
#include "Hardware.h"
#include "Adafruit_NeoPixel.h"

class Bottom : public Hardware
{
public:
    Bottom(const bool& enabled = false)
    {
        _enabled = enabled;
    };
    void init() override;
    void update() override;

    int getAngel();

private:
    // void seesLine();
    bool _seesLine;
    int _angle = -1;
    Adafruit_NeoPixel bottom = Adafruit_NeoPixel(BOTTOM_LENGTH, BOTTOM_LED, NEO_GRB + NEO_KHZ800); // OBJEKTINITIALISIERUNG (BODEN-LEDS)
};