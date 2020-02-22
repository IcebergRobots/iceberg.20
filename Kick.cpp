#include "Kick.h"

void Kick::init()
{
    if (getEn())
    {
        LogKick("enabled");
        pinMode(KICKER, OUTPUT);
        LogKick("Initilized");
    }else   
        LogKick("disabled");
}

void Kick::update()
{
    if (millis() - _timer > 200 && getEn())
        analogWrite(KICKER, 0);
}

void Kick::kick()
{
    if (getEn() && _calibrated)
    {
        _timer = millis();
        analogWrite(KICKER, _power); // schuss bei 12, Poti bei A0
    }
 }
 
 void Kick::setCali(const bool& caliKick)
 {
     _calibrated = caliKick;
 }

 const bool Kick::getCali()
 {
     return _calibrated;
 }

 void Kick::setPower(const unsigned int& power)
 {
     _power = power;
     setCali(true); 
 }

 const int Kick::getPower()
 {
     return _power;
 }