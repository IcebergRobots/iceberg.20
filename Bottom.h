#pragma once

#include "Config.h"
#include "Hardware.h"
#include "Adafruit_NeoPixel.h"

#define BOTTOM_LENGTH 40        // [0 bis *] Anzahl der Boden-Leds

class Bottom : public Hardware
{
public:
    Bottom(const bool& enabled = false)
    {
        _enabled = enabled;
    };
    void init() override;
    void update() override;

    bool seesLine();

private:
    Adafruit_NeoPixel _bottom = Adafruit_NeoPixel(BOTTOM_LENGTH, BOTTOM_LED, NEO_GRB + NEO_KHZ800); // OBJEKTINITIALISIERUNG (BODEN-LEDS)
    bool _seesLine;
    int _angle = -1;
};