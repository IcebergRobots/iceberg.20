#include "Ultrasonic.h"

void Ultrasonic::init()
{
    if (getEn())
    {
        LogUs("enabled");
        // for (int i = 0; i < NUM_OF_US; i++)
        // {
        //     I2c.write(_addresses[i], byte(0x02));
        //     // I2c.write(byte(70)); //warum 70? sehe im datenblatt nichts
        //     I2c.endTransmission();
        // }
        LogUs("Initlized");
    }else
        LogUs("disabled");
}

void Ultrasonic::update()
{
    if (getEn())
    {
        if (millis() - _lastMeasurement > 25 && !_fetched)
        {
            fetch();
            _fetched = true;
        }
        if (millis() - _lastMeasurement > 65)
        {
            I2c.write(0, byte(0x00), byte(0x51));
            _lastMeasurement = millis();
            _fetched = false;
        }
    }
}

void Ultrasonic::fetch()
{
    for (int i = 0; i < NUM_OF_US; i++)
    {
        I2c.write(_addresses[i], byte(0x02));
        I2c.read((int)_addresses[i], (int)2);

        if (2 <= I2c.available())
        {
            _distance[i] = I2c.receive() << 8;
            _distance[i] |= I2c.receive();
        }
    }
}

int Ultrasonic::getFrontLeft() { return _distance[0]; }
int Ultrasonic::getLeft() { return _distance[1]; }
int Ultrasonic::getBack() { return _distance[2]; }
int Ultrasonic::getRight() { return _distance[3]; }
int Ultrasonic::getFrontRight() { return _distance[4]; }
int Ultrasonic::getFront() { return min(getFrontLeft(), getFrontRight()); }
