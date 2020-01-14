#include "Ultrasonic.h"

Ultrasonic::Ultrasonic()
{
    //  warum initialisiert man nicht hier direkt, sondern erst durch einen extra Methodenaufruf
}

void Ultrasonic::init()
{
    for (int i = 0; i < NUM_OF_US; i++)
    {
        Wire.beginTransmission(_addresses[i]);
        Wire.write(byte(0x02));
        Wire.write(byte(70)); //warum 70? sehe im datenblatt nichts
        Wire.endTransmission();
    }
}

void Ultrasonic::fetch()
{
    for (int i = 0; i < NUM_OF_US; i++)
    {
        Wire.beginTransmission(_addresses[i]);
        Wire.write(byte(0x02));
        Wire.endTransmission();
        Wire.requestFrom((int)_addresses[i], (int)2);

        if (2 <= Wire.available())
        {
            _distance[i] = Wire.read() << 8;
            _distance[i] |= Wire.read();
        }
    }
}

void Ultrasonic::update()
{
    if (millis() - _lastMeasurement > 25 && !_fetched)
    {
        fetch();
        _fetched = true;
    }
    if (millis() - _lastMeasurement > 65)
    {
        Wire.beginTransmission(0); // auf Adresse 0 hören alle Ultraschallsensor zu. Alternativ können die Befehle an alle Sonsoren einzeln gesendet werden.
        Wire.write(byte(0x00));
        Wire.write(byte(0x51));
        Wire.endTransmission();

        _lastMeasurement = millis();
        _fetched = false;
    }
}

int Ultrasonic::getFrontLeft() { return _distance[0]; }
int Ultrasonic::getLeft() { return _distance[1]; }
int Ultrasonic::getBack() { return _distance[2]; }
int Ultrasonic::getRight() { return _distance[3]; }
int Ultrasonic::getFrontRight() { return _distance[4]; }
int Ultrasonic::getFront() { return min(getFrontLeft(), getFrontRight()); }
