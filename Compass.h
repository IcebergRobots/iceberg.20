#ifndef Compass_h
#define Compass_h

#include "Config.h"

#define COMPASS_ADRESS 96

class Compass
{

    public:
        Compass();
        void init();
        float angle();
        void update();
    private:
        const int ardess = COMPASS_ADRESS;
};

#endif
