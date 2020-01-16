//Datasheet: http://coecsl.ece.illinois.edu/ge423/DevantechSRF08UltraSonicRanger.pdf

#pragma once
#include "Config.h"
#include "Hardware.h"

class Ultrasonic : public Hardware
{
public:
    Ultrasonic();

    void init() override; //kein return?
    void update() override;

    int getRight();
    int getLeft();
    int getBack();
    int getFrontLeft();
    int getFrontRight();

    int getFront();

private:
    void fetch();
    bool _fetched = true;

    unsigned long _lastMeasurement = 0;
    const byte _addresses[NUM_OF_US] = {FRONT_LEFT, LEFT, BACK, RIGHT, FRONT_RIGHT}; //vorher progmen, um im flash und nicht im sram zu speichern, braucht bestimmte funktionen um wert auszulesen, diese wurden nicht benutzt
    int _distance[NUM_OF_US] = {0, 0, 0, 0, 0};
};



