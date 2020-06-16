#include "Ultrasonic.h"

void Ultrasonic::init()
{
    if (getEn())
    {
        LogUs("enabled");
        for (int i = 0; i < NUM_OF_US; i++)
            I2c.write(_addresses[i], 0x02, 0x46);
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
            filter();
            _fetched = true;
        }
        if (millis() - _lastMeasurement > 65)
        {
            I2c.write(0, 0x00, 0x51);
            _lastMeasurement = millis();
            _fetched = false;
        }
    }
}

void Ultrasonic::fetch()
{
    for (int i = 0; i < NUM_OF_US; i++)
    {
        I2c.write(_addresses[i], 0x02);
        I2c.read((int)_addresses[i], (int)2);

        if (2 <= I2c.available())
        {
            for(int j = 0; j < FILTER_VALUES - 1; j++ )
            {
                _distance[i][j] = _distance[i][j+1];
            }
            _distance[i][FILTER_VALUES-1] = I2c.receive() << 8;
            _distance[i][FILTER_VALUES-1] |= I2c.receive();
        }
    }
}

void Ultrasonic::filter()
{
    int distanceSum = 0;
    for(int i = 0; i < NUM_OF_US;i ++)
    {
        for(int j = 0; j < FILTER_VALUES; j++)
        {
            distanceSum += _distance[i][j];
        }
        _filteredDistance[i] = distanceSum / FILTER_VALUES;
        distanceSum = 0;
    }
}

int Ultrasonic::getFrontLeft() { return _filteredDistance[0]; }
int Ultrasonic::getLeft() { return _filteredDistance[1]; }
int Ultrasonic::getBack() { return _filteredDistance[2]; }
int Ultrasonic::getRight() { return _filteredDistance[3]; }
int Ultrasonic::getFrontRight() { return _filteredDistance[4]; }
int Ultrasonic::getFront() { return min(getFrontLeft(), getFrontRight()); }
