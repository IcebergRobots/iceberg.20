#include "Pui.h"

Adafruit_MCP23017 expander;

void Pui::init()
{
    if (getEn())
    {
        LogPui("enabled");
        //new PUI
        // expander.begin(0);

        // expander.pinMode(S_KICKER, INPUT);
        // expander.pinMode(S_MOTOR, INPUT);
        // expander.pinMode(S_HEADSTART, INPUT);

        // expander.pinMode(B_KICK, INPUT);
        // expander.pullUp(B_KICK, HIGH);
        // expander.pinMode(B_SHIFT, INPUT);
        // expander.pullUp(B_SHIFT, HIGH);
        // expander.pinMode(B_CAL, INPUT);
        // expander.pullUp(B_CAL, HIGH);

        // expander.pinMode(LED_DEFENDER, OUTPUT);

        //OLD pUI
        pinMode(BUTTON_START, INPUT_PULLUP);
        pinMode(BUTTON_STOP, INPUT_PULLUP);
        pinMode(ROTARY_BUTTON, INPUT_PULLUP);
        pinMode(ROTARY_A, INPUT_PULLUP);
        pinMode(ROTARY_B, INPUT_PULLUP);

        mcp.begin();

        for (int i = 0; i < 16; i++)
        {
            mcp.pinMode(i, INPUT);
            mcp.pullUp(i, HIGH);
        }
        LogPui("Initilized");
    }
    else
        LogPui("disabled");
}

void Pui::update()
{
    if (getEn())
    {
        //new PUI
        // _SKicker = expander.digitalRead(S_KICKER);
        // _SHeadstart = expander.digitalRead(S_HEADSTART);
        // _SMotor = expander.digitalRead(S_MOTOR);

        //old PUI
        if (millis() > inputTimer + 20)
        {

        button_start       = last_button_start && !digitalRead(BUTTON_START);
        button_stop        = last_button_stop && !digitalRead(BUTTON_STOP);
        button_encoder     = last_button_encoder && !digitalRead(ROTARY_BUTTON);
        button_kick        = last_button_kick && ! mcp.digitalRead(PIN_MCP_kick); //UPDATE
        button_compass     = last_button_compass && ! mcp.digitalRead(PIN_MCP_compass);
        button_animation   = last_button_animation && ! mcp.digitalRead(PIN_MCP_animation);
        button_line        = last_button_line && ! mcp.digitalRead(PIN_MCP_line);
        button_lightBarrierCalibration = last_button_lightBarrierCalibration && ! mcp.digitalRead(PIN_MCP_lightBarrierCalibration);
        button_left        = last_button_left && ! mcp.digitalRead(PIN_MCP_left);
        button_middle      = last_button_middle && ! mcp.digitalRead(PIN_MCP_middle);
        button_right       = last_button_right && ! mcp.digitalRead(PIN_MCP_right);
        switch_headstart   = last_switch_headstart &&! mcp.digitalRead(PIN_MCP_SW_headstart);
        switch_motor       = last_switch_motor &&! mcp.digitalRead(PIN_MCP_SW_motor);          //UPDATE
        switch_bluetooth   = last_switch_bluetooth &&! mcp.digitalRead(PIN_MCP_SW_bluetooth);
        switch_kick        = last_switch_kick &&! mcp.digitalRead(PIN_MCP_SW_kick);           //UPDATE
        switch_bodensensor = last_switch_bodensensor &&! mcp.digitalRead(PIN_MCP_SW_bodensensor);
        switch_debug       = last_switch_debug &&! mcp.digitalRead(PIN_MCP_SW_debug);          //UPDATE
        
        last_button_start       = !digitalRead(BUTTON_START);
        last_button_stop        = !digitalRead(BUTTON_STOP);
        last_button_encoder     = !digitalRead(ROTARY_BUTTON);
        last_button_kick        = ! mcp.digitalRead(PIN_MCP_kick); //UPDATE
        last_button_compass     = ! mcp.digitalRead(PIN_MCP_compass);
        last_button_animation   = ! mcp.digitalRead(PIN_MCP_animation);
        last_button_line        = ! mcp.digitalRead(PIN_MCP_line);
        last_button_lightBarrierCalibration = ! mcp.digitalRead(PIN_MCP_lightBarrierCalibration);
        last_button_left        = ! mcp.digitalRead(PIN_MCP_left);
        last_button_middle      = ! mcp.digitalRead(PIN_MCP_middle);
        last_button_right       = ! mcp.digitalRead(PIN_MCP_right);
        last_switch_headstart   = ! mcp.digitalRead(PIN_MCP_SW_headstart);
        last_switch_motor       = ! mcp.digitalRead(PIN_MCP_SW_motor);          //UPDATE
        last_switch_bluetooth   = ! mcp.digitalRead(PIN_MCP_SW_bluetooth);
        last_switch_kick        = ! mcp.digitalRead(PIN_MCP_SW_kick);           //UPDATE
        last_switch_bodensensor = ! mcp.digitalRead(PIN_MCP_SW_bodensensor);
        last_switch_debug       = ! mcp.digitalRead(PIN_MCP_SW_debug);          //UPDATE
        }
    }
}

//NEW PUI
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