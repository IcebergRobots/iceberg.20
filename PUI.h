#pragma once 

#include "Config.h"
#include "Hardware.h"
#include <Adafruit_MCP23017.h>



class PUI : public Hardware
{
    public:
        PUI();

        void init() override;
        void update() override;
        
        bool getSKicker();
        bool getSHeadstart();
        bool getSMotor();

        bool getBKick();

        
    private:
        bool SKicker = false;
        bool SHeadstart = false;
        bool SMotor = false;
        bool BKick = false;
        unsigned long timer = 0;

    

};