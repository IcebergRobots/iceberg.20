#include "Pui.h"

Adafruit_MCP23017 expander;

void Pui::init()
{
    if (getEn())
    {
        LogPui("enabled");
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
        LogPui("Initilized");
    }else
        LogPui("disabled");
}

void Pui::update()
{
    if (getEn())
    {
        _SKicker = expander.digitalRead(S_KICKER);
        _SHeadstart = expander.digitalRead(S_HEADSTART);
        _SMotor = expander.digitalRead(S_MOTOR);
    }
}

bool Pui::getSKicker()
{
    return _SKicker;
}

bool Pui::getSHeadstart()
{
    return _SHeadstart;
}

bool Pui::getSMotor()
{
    return _SMotor;
}

bool Pui::getBKick()
{
    return _BKick;
}