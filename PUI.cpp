#include "PUI.h"

Adafruit_MCP23017 expander;

void PUI::init()
{
    if (getEn())
    {
        expander.begin(0);

        expander.pinMode(S_KICKER, INPUT);
        expander.pinMode(S_MOTOR, INPUT);
        expander.pinMode(S_HEADSTART, INPUT);

        expander.pinMode(B_KICK, INPUT);
        expander.pullUp(B_KICK, HIGH);
        expander.pinMode(B_SHIFT, INPUT);
        expander.pullUp(B_SHIFT, HIGH);
        expander.pinMode(B_CAL, INPUT);
        expander.pullUp(B_CAL, HIGH);

        expander.pinMode(LED_DEFENDER, OUTPUT);
    }
}

void PUI::update()
{
    if (getEn())
    {
        _SKicker = expander.digitalRead(S_KICKER);
        _SHeadstart = expander.digitalRead(S_HEADSTART);
        _SMotor = expander.digitalRead(S_MOTOR);
    }
}

bool PUI::getSKicker()
{
    return _SKicker;
}

bool PUI::getSHeadstart()
{
    return _SHeadstart;
}

bool PUI::getSMotor()
{
    return _SMotor;
}

bool PUI::getBKick()
{
    return _BKick;
}