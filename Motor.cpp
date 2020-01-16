#include "Motor.h"

Motor::Motor()
{

}

void Motor::init() 
{
    pinMode(this->_fwd, OUTPUT); // definiere Pins als Output
    pinMode(this->_bwd, OUTPUT);
    pinMode(this->_pwm, OUTPUT);
}

void Motor::update()
{
    //TODO  reading EncoderSignals
}

void Motor::steerMotor()
{
    if (this->_motEn)
  {
    this->_power = min(255, this->_power); //Eingabekorrektur
    this->_power = max(-255, this->_power);

    digitalWrite(this->_fwd, this->_power > 0);  //drehe Motor vorwarts
    digitalWrite(this->_bwd, this->_power <= 0); //drehe Motor rueckwaerts
    analogWrite(this->_pwm, abs(this->_power));  //drehe Motor mit Geschwindigkeit
  }
  else
  {
    this->brake(false); //Muss ich machen, sonst fahren die weiter auch wenn disabled
  }
}

/*****************************************************
  bremse aktiv oder passiv alle Motoren
  @param activ: aktives Bremsen?
*****************************************************/
void Motor::brake(bool activ)
{
    digitalWrite(this->_fwd, activ);
    digitalWrite(this->_bwd, activ);
    analogWrite(this->_pwm, 255);
}

void Motor::setMotEn(bool _motEn)
{
    this->_motEn = _motEn;
}

bool Motor::getMotEn()
{
    return this->_motEn;
}

void Motor::setPower(int power)
{
  this->_power = power;
}