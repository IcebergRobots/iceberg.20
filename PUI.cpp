#include "PUI.h"

PUI::PUI(){
    
}

void PUI::init(){
    Adafruit_MCP23017::begin(0);

    Adafruit_MCP23017::pinMode(S_KICKER, INPUT);
    Adafruit_MCP23017::pinMode(S_MOTOR, INPUT);
    Adafruit_MCP23017::pinMode(S_HEADSTART, INPUT);

    Adafruit_MCP23017::pinMode(B_KICK, INPUT);
    Adafruit_MCP23017::pullUp(B_KICK, HIGH);
    Adafruit_MCP23017::pinMode(B_SHIFT, INPUT);
    Adafruit_MCP23017::pullUp(B_SHIFT, HIGH);
    Adafruit_MCP23017::pinMode(B_CAL, INPUT);
    Adafruit_MCP23017::pullUp(B_CAL, HIGH);

    Adafruit_MCP23017::pinMode(LED_DEFENDER, OUTPUT);
}

void PUI::update(){

}