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
    while (_counter < 20)
    {

        if (_state == LED_ON && millis() - _onTimer > 10)
        {
            turnOff();
            _counter++;
            calculate();
            _summe += _value;
        }
        else if (_state == LED_OFF && millis() - _offTimer > 10)
        {
            turnOn();
        }
    }
    _thresholdNoBall = _summe / 20;

    //as long no display, visual message to calibrate with ball todo
    _counter = 0;
    _summe = 0;

    while (millis() - _onTimer < 5000)
    {
        digitalWrite(LED_PIN, HIGH);
    }
    digitalWrite(LED_PIN, LOW);
    _state == LED_OFF;
    //with ball
    while (_counter < 20)
    {

        if (_state == LED_ON && millis() - _onTimer > 10)
        {
            turnOff();
            _counter++;
            calculate();
            _summe += _value;
        }
        else if (_state == LED_OFF && millis() - _offTimer > 10)
        {
            turnOn();
        }
    }
    _thresholdBall = _summe / 20;
    _threshold = (_thresholdBall + _thresholdNoBall) / 2;
    
    while (millis() - _onTimer < 2000)
    {
        digitalWrite(LED_PIN, HIGH);
    }
    digitalWrite(LED_PIN, LOW);
    _state == LED_OFF;
}

void BallTouch::calibrateNoBall() {
    _counter = 0;
    _summe = 0;
    //without Ball
    while (_counter < 20)
    {

        if (_state == LED_ON && millis() - _onTimer > 10)
        {
            turnOff();
            _counter++;
            calculate();
            _summe += _value;
        }
        else if (_state == LED_OFF && millis() - _offTimer > 10)
        {
            turnOn();
        }
    }
    _thresholdNoBall = _summe / 20;
    digitalWrite(LED_PIN, LOW);
    _state == LED_OFF;
}

void BallTouch::calibrateBall() {
     _counter = 0;
    _summe = 0;
    //with ball
    while (_counter < 20)
    {

        if (_state == LED_ON && millis() - _onTimer > 10)
        {
            turnOff();
            _counter++;
            calculate();
            _summe += _value;
        }
        else if (_state == LED_OFF && millis() - _offTimer > 10)
        {
            turnOn();
        }
    }
    _thresholdBall = _summe / 20;
    digitalWrite(LED_PIN, LOW);
    _state == LED_OFF;
}

void BallTouch::calculateTreshold() {
    if (_thresholdBall != 0)
    {
        caliBall = true;
        if (_thresholdNoBall != 0)
        {
        _threshold = (_thresholdBall + _thresholdNoBall) / 2;
        caliNoBall = true;
        }
    }
}

void BallTouch::update()
{
    if(calibrated) {
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
    
}

int BallTouch::getValue() { return _value; }
int BallTouch::getThreshold() { return _threshold; }
int BallTouch::getBallThreshold() { return _thresholdBall; }
int BallTouch::getNoBallThreshold() { return _thresholdNoBall; }

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