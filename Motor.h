#pragma once

#include "Config.h"
#include "Hardware.h"

class Motor : public Hardware
{
    public:
        Motor(byte fwd, byte bwd, byte pwm, int curSens)
           : _fwd(fwd), _bwd(bwd), _pwm(pwm), _curSens(curSens) {}
        Motor();
        void init() override;
        void update() override; //TODO Encodersignals

        void steerMotor();

        void brake(bool active);

        void setPower(int power);

    private:
        byte _fwd;
        byte _bwd;
        byte _pwm;
        int _curSens;
        
        int _power; //zwischenspeicher
    
};