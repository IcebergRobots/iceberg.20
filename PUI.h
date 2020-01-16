#pragma once 

#include "Config.h"
#include <Adafruit_MCP23017.h>


class PUI: private Adafruit_MCP23017 
{
    public:
        PUI();

        void init();
        void update();
        
    private:

};