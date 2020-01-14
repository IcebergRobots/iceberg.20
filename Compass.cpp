// Einstellungen:
#include "Compass.h"

Compass::Compass()
{
}

void Compass::init()
{
  Wire.beginTransmission(COMPASS_ADRESS);
  Wire.write(0x01); //Sends the register we wish to start reading from
  Wire.endTransmission();
}

void Compass::update()
{

  // Request 5 bytes from the CMPS12
  // this will give us the 8 bit bearing,
  // both bytes of the 16 bit bearing, pitch and roll
  Wire.requestFrom(COMPASS_ADRESS, 5);

  while (Wire.available() < 5); // Wait for all bytes to come back

  _angle8 = Wire.read(); // Read back the 5 bytes
  _high_byte = Wire.read();
  _low_byte = Wire.read();
  _pitch = Wire.read();
  _roll = Wire.read();

  _angle16 = _high_byte; // Calculate 16 bit angle
  _angle16 <<= 8;
  _angle16 += _low_byte;
}

float Compass::getAngle8() { return _angle8; }
int Compass::getAngle16() { return _angle16 / 10; }
int Compass::getPitch() { return _pitch; }
int Compass::getRoll() { return _roll; }