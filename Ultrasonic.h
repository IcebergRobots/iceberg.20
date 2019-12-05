//Datasheet: http://coecsl.ece.illinois.edu/ge423/DevantechSRF08UltraSonicRanger.pdf

#ifndef Ultrasonic_h
#define Ultrasonic_h 

#include "Config.h"

//addresses of the Ultrasonicsensors named by their position
#define NUM_OF_US 5
#define FRONT_LEFT 112
#define LEFT 113
#define FRONT_RIGHT 116
#define BACK 114
#define RIGHT 115

class Ultrasonic
{
public:
    Ultrasonic();
    int right();
    int left();
    int back();
    int frontLeft();
    int frontRight();

    int front();

    void init();         //kein return?
    void update();

private:
    void fetch();
    bool fetched = true;

    unsigned long lastMeasurement = 0;
    const byte addresses[NUM_OF_US] = {FRONT_LEFT, LEFT, FRONT_RIGHT, BACK, RIGHT}; //vorher progmen, um im flash und nicht im sram zu speichern, braucht bestimmte funktionen um wert auszulesen, diese wurden nicht benutzt
    int distance[NUM_OF_US] = {0, 0, 0, 0, 0};
};
#endif
