#pragma once

#include "Config.h"

class Motor
{
    public:
        Motor(byte fwd, byte bwd, byte pwm, int curSens)
           : _fwd(fwd), _bwd(bwd), _pwm(pwm), _curSens(curSens) {}
        Motor();
        void init();
        void update(); //TODO Encodersignals

        void steerMotor();

        void brake(bool active);

        void setMotEn(bool motEn);
        bool getMotEn();

        void setPower(int power);

    private:
        byte _fwd;
        byte _bwd;
        byte _pwm;
        int _curSens;
        
        bool _motEn;

        int _power; //zwischenspeicher
    
};