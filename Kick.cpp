#include "Kick.h"

void Kick::init()
{
    pinMode(KICKER, OUTPUT);
}

void Kick::update()
{
    if (millis() - _kickTimer > 200)
        analogWrite(KICKER, 0);
}

void Kick::kick()
{
    if (enKick && caliKick)
    {
        _kickTimer = millis();
        analogWrite(KICKER, _kickPower); // schuss bei 12, Poti bei A0
    }
 }

 void Kick::setKickPower(const unsigned int& kickPower)
 {
     _kickPower = kickPower;
 }

 const int Kick::getKickPower()
 {
     return _kickPower;
 }