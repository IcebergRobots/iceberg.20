#pragma once

#include "Motor.h"
#include "Config.h"
#include "Hardware.h"

#define ANGLE 70   //Angle between motors
class Chassis : public Hardware
{
  public:
    void init() override;
    void update() override; //TODO Encoder

    void calculate(int angle, int power, int rotation = 0);
    void drive();

    void drive(int angle, int power, int rotation = 0);

    void brake(bool activ);

    void setMotEn(bool motEn);
    bool getMotEn();

  private:
    Motor motors[4];
    bool _motEn;
};
