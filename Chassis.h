#pragma once

#include "Motor.h"
#include "Config.h"
#include "Hardware.h"

#define ANGLE 70 //Angle between motors
#define NUM_OF_M 4

class Chassis : public Hardware
{
public:
  Chassis(const bool& motEn = false);

  void init() override;
  void update() override; //TODO Encoder

  void calculate(int angle, int power, int rotation = 0);
  void drive();

  void drive(int angle, int power, int rotation = 0);

  void brake(const bool& activ);

  void setMotEn(const bool& motEn);
  const bool getMotEn(); //neew this because the enable way is a different by the motors

private:
  bool _motEn;
  Motor motors[4];
};
