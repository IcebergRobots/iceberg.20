#ifndef Display_h
#define Display_h

#include "Config.h"

#define NUM_OBJECTS 4

class Display
{
public:
    static void init();
    static void update();
private:
Display();
    static void bLedOnPopCallback(void *ptr);
    static void bLedOffPopCallback(void *ptr);
    static void hLedSliderPopCallback(void *ptr);

    //Beispiel Objects
    static NexText _tLedState;
    static NexButton _bLedOn;
    static NexButton _bLedOff;
    static NexSlider _hLedSlider;

    static NexTouch *_nex_listen_list[NUM_OBJECTS];

    static const int _led1 = 6;
};
#endif
