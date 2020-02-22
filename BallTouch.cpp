#include "BallTouch.h"

void BallTouch::init()
{
    _threshold = EEPROM.read(EEPROM_BALLTOUCH_THRESHOLD);
    if(getEn())
    {
        LogBalltouch("enabled");
        pinMode(LED_PIN, OUTPUT);
        pinMode(SENSOR_PIN, INPUT_PULLUP);
        LogBalltouch("Gets Threshold: " + _threshold);
        LogBalltouch("Intialized");
    } else 
        LogBalltouch("disabled");
}

void BallTouch::calibrate()
{
    if(getEn())
    {
    calibrateNoBall();

    while (millis() - _onTimer < 2000)
        digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);

    calibrateBall();
    calculateTreshold();
    }
}

void BallTouch::calibrateNoBall()
{

    _summe = 0;
    _counter = 0;
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
            turnOn();
    }
    _thresholdNoBall = _summe / 20;
    digitalWrite(LED_PIN, LOW);
    _state == LED_OFF;
}

void BallTouch::calibrateBall()
{
    _summe = 0;
    _counter = 0;

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
            turnOn();
    }
    _thresholdBall = _summe / 20;
    digitalWrite(LED_PIN, LOW);
    _state == LED_OFF;
}

void BallTouch::calculateTreshold()
{
    if (_thresholdBall > -1)
    {
        if (_thresholdNoBall > -1)
        {
            _threshold = (_thresholdBall + _thresholdNoBall) / 2;
            EEPROM.write(EEPROM_BALLTOUCH_THRESHOLD, _threshold);
            LogBalltouch("Sets threshold to: " + _threshold);
            LogBalltouch("Calibrated");
        }
    }
}

void BallTouch::update()
{
    if (getEn())
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
    }else
        digitalWrite(LED_PIN, LOW);
    
}

int BallTouch::getValue() { return _value; }
int BallTouch::getThreshold() { return _threshold; }
int BallTouch::getBallThreshold() { return _thresholdBall; }
int BallTouch::getNoBallThreshold() { return _thresholdNoBall; }

bool BallTouch::hasBall()
{
    if(getEn())
    {
    LogBalltouch("Sees Ball: " + (_value > _threshold));    
    return _value > _threshold;
    }
    return 0;
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