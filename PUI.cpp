#include "PUI.h"

Adafruit_MCP23017 expander;

PUI::PUI(){
    
}

void PUI::init(){
    expander.begin(0);

    expander.pinMode(S_KICKER, INPUT);
    expander.pinMode(S_MOTOR, INPUT);
    expander.pinMode(S_HEADSTART, INPUT);

    expander.pinMode(B_KICK, INPUT);
    expander.pullUp(B_KICK, HIGH);
    expander.pinMode(B_SHIFT, INPUT);
    expander.pullUp(B_SHIFT, HIGH);
    expander.pinMode(B_CAL, INPUT);
    expander.pullUp(B_CAL, HIGH);

    expander.pinMode(LED_DEFENDER, OUTPUT);
}

void PUI::update(){
    SKicker = expander.digitalRead(S_KICKER);
    SHeadstart = expander.digitalRead(S_HEADSTART);
    SMotor = expander.digitalRead(S_MOTOR);
    
}

bool PUI::getSKicker(){
    return SKicker;
}

bool PUI::getSHeadstart(){
    return SHeadstart;
}

bool PUI::getSMotor(){
    return SMotor;
}

bool PUI::getBKick(){
    return BKick;
}