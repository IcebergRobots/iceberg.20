#pragma once 

#include "Config.h"
#include "Hardware.h"
#include <Adafruit_MCP23017.h>



class PUI : public Hardware
{
    public:
        PUI(const bool& enabled = false)
        {
            _enabled = enabled;
        };

        void init() override;
        void update() override;

        bool getSKicker();
        bool getSHeadstart();
        bool getSMotor();

        bool getBKick();

        
    private:
        bool _SKicker;
        bool _SHeadstart;
        bool _SMotor;
        bool _BKick;
        unsigned long _timer;

    

};