#pragma once 

#include "Config.h"
#include "Hardware.h"
#include <Adafruit_MCP23017.h>

//old PUI
//IO-Expander:    
#define PIN_MCP_kick            8
#define PIN_MCP_compass         12
#define PIN_MCP_animation       13
#define PIN_MCP_line            14
#define PIN_MCP_lightBarrierCalibration 15

#define PIN_MCP_left            11
#define PIN_MCP_middle          10
#define PIN_MCP_right           9



#define BUTTON_START    22
#define BUTTON_STOP     24

#define ROTARY_BUTTON   30  //  Rotary Encoder Taster
#define ROTARY_A        26  //  Rotary Encoder Rotation A
#define ROTARY_B        28  //  Rotary Encoder Rotation B

// Switches
#define PIN_MCP_SW_headstart    0
#define PIN_MCP_SW_motor        1
#define PIN_MCP_SW_bluetooth    2
#define PIN_MCP_SW_kick         3
#define PIN_MCP_SW_bodensensor  4
#define PIN_MCP_SW_debug        5

class Pui : public Hardware
{
    public:
        Pui(const bool& enabled = false)
        {
            _enabled = enabled;
        };

        void init() override;
        void update() override;

        //old PUI
        bool button_encoder = true;
    // PUI:
        // Buttons
        bool button_start       = false;
        bool button_stop        = false;
        bool button_kick      = true;
        bool button_compass     = false;
        bool button_animation   = false;
        bool button_line        = false;
        bool button_lightBarrierCalibration = false;

        bool button_left        = false;
        bool button_middle      = false;
        bool button_right       = false;

        // Switches
        bool switch_headstart   = false;
        bool switch_motor     = false;
        bool switch_bluetooth   = false;
        bool switch_kick      = false;
        bool switch_bodensensor = false;
        bool switch_debug     = false;


        //new PUI
        bool getSKicker();
        bool getSHeadstart();
        bool getSMotor();

        bool getBKick();

        
    private:

        Adafruit_MCP23017 mcp;

        unsigned long inputTimer = 0;

        bool last_button_encoder = true;
    // PUI:
        // Buttons
        bool last_button_start       = false;
        bool last_button_stop        = false;
        bool last_button_kick      = true;
        bool last_button_compass     = false;
        bool last_button_animation   = false;
        bool last_button_line        = false;
        bool last_button_lightBarrierCalibration = false;

        bool last_button_left        = false;
        bool last_button_middle      = false;
        bool last_button_right       = false;

        // Switches
        bool last_switch_headstart   = false;
        bool last_switch_motor     = false;
        bool last_switch_bluetooth   = false;
        bool last_switch_kick      = false;
        bool last_switch_bodensensor = false;
        bool last_switch_debug     = false;

        //new PUI
        bool _SKicker;
        bool _SHeadstart;
        bool _SMotor;
        bool _BKick;
        unsigned long _timer;

    

};