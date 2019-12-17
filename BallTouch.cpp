#include "BallTouch.h"

BallTouch::BallTouch()
{
}

void BallTouch::init()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(SENSOR_PIN, INPUT_PULLUP);
}

void BallTouch::calibrate()
{
    _counter = 0;
    _summe = 0;
    //without Ball
    while (_counter < 10)
    {

        if (_state == LED_ON && millis() - _onTimer > 10)
        {
            turnOff();
            calculate();
            _summe += _value;
        }
        else if (_state == LED_OFF && millis() - _offTimer > 10)
        {
            turnOn();
        }
        _counter++;
    }
    _thresholdNoBall = _summe / 10;
    //as long no display, visual message to calibrate with ball todo
    _counter = 0;
    _summe = 0;
    while (millis() - _onTimer < 5000)
    {
        digitalWrite(LED_PIN, HIGH);
    }

        //with ball
    while (_counter < 10)
    {

        if (_state == LED_ON && millis() - _onTimer > 10)
        {
            turnOff();
        }
        else if (_state == LED_OFF && millis() - _offTimer > 10)
        {
            turnOn();
            calculate();
            _summe += _value;
        }
        _counter++;
    }
    _thresholdBall = _summe / 10;
    _threshold = (_thresholdBall + _thresholdNoBall) /2;
}

void BallTouch::update()
{
    if (_state == LED_ON && millis() - _onTimer > 10)
    {
        turnOff();
        calculate();
    }
    else if (_state == LED_OFF && millis() - _offTimer > 10)
    {
        turnOn();
        calculate();
    }
}

int BallTouch::getValue()
{
    return _value;
}

int BallTouch::getTheshold() {
    return _threshold;
}

bool BallTouch::hasBall()
{
    return _value > _threshold;
}

void BallTouch::turnOn()
{
    _darkValue = analogRead(SENSOR_PIN);
    digitalWrite(LED_PIN, HIGH);
    _onTimer = millis();
    _state = LED_ON;
}

void BallTouch::turnOff()
{
    _lightValue = analogRead(SENSOR_PIN);
    digitalWrite(LED_PIN, LOW);
    _offTimer = millis();
    _state = LED_OFF;
}

void BallTouch::calculate()
{
    _value = (_darkValue - _lightValue);
}