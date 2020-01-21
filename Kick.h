#pragma once

#include "Config.h"
#include "Hardware.h"

class Kick : public Hardware
{
    public:
        Kick(int kickPower)
            : _kickPower(kickPower) {};
        void init() override;
        void update() override;
        
        void kick();

        void setKickPower(const unsigned int& kickPower);
        const int getKickPower();
    private:
        unsigned long _kickTimer;
        unsigned int _kickPower;
};