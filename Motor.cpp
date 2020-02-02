#include "Motor.h"

Motor::Motor()
{
}

void Motor::init()
{  
  if (true)               //getEn() geht nicht wegen Gründen
  {
    pinMode(_fwd, OUTPUT); // definiere Pins als Output
    pinMode(_bwd, OUTPUT);
    pinMode(_pwm, OUTPUT);
  }
}

void Motor::update()
{
  if (getEn())
  {
    /* code */
  }

  //TODO  reading EncoderSignals
}

void Motor::steerMotor()
{   
  if (true)                     //getEn() geht nicht wegen Gründen
  {
    _power = min(255, _power); //Eingabekorrektur
    _power = max(-255, _power);

    digitalWrite(_fwd, _power > 0);  //drehe Motor vorwarts
    digitalWrite(_bwd, _power <= 0); //drehe Motor rueckwaerts
    analogWrite(_pwm, abs(_power));  //drehe Motor mit Geschwindigkeit
  }
  else
  {
    brake(false); //Muss ich machen, sonst fahren die weiter auch wenn disabled
  }
}

/*****************************************************
  bremse aktiv oder passiv alle Motoren
  @param activ: aktives Bremsen?
*****************************************************/
void Motor::brake(const bool& activ)
{
  digitalWrite(_fwd, activ);
  digitalWrite(_bwd, activ);
  analogWrite(_pwm, 255);
}

void Motor::setPower(int power)
{
  _power = power;
}