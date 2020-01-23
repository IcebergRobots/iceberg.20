#pragma once

#include "Config.h"
#include "Hardware.h"

class Kick : public Hardware
{
    public:
        Kick(const bool& enabled = false, const int& power = 0)
            {
                _enabled = enabled;
                setPower(power);            //setCali = true
            };
        void init() override;
        void update() override;

        void setCali(const bool& calibrated);
        const bool getCali();

        void kick();

        void setPower(const unsigned int& kickPower);
        const int getPower();
    private:
        bool _calibrated;
        unsigned long _timer;
        unsigned int _power;
};