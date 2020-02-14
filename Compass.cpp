// Einstellungen:
#include "Compass.h"

void Compass::init()
{
  if (getEn())
  {
    
  }
}

void Compass::update()
{
  if (getEn())
  {
    Wire.beginTransmission(COMPASS_ADRESS);
    Wire.write(0x01); //Sends the register we wish to start reading from
    Wire.endTransmission();
    // Request 5 bytes from the CMPS12
    // this will give us the 8 bit bearing,
    // both bytes of the 16 bit bearing, pitch and roll
    Wire.requestFrom(COMPASS_ADRESS, 5);
    
    if (Wire.available() >= 5)
    {
      _angle8 = Wire.read(); // Read back the 5 bytes
      _high_byte = Wire.read();
      _low_byte = Wire.read();
      _pitch = Wire.read();
      _roll = Wire.read();

      _angle16 = _high_byte; // Calculate 16 bit angle
      _angle16 <<= 8;
      _angle16 += _low_byte;
    }
  }
}

void Compass::storeCalibration()
{
  Wire.beginTransmission(COMPASS_ADRESS);
  Wire.write(0x00); //Sends the register we wish to start reading from
  Wire.write(0xF0);
  Wire.endTransmission();
  delay(20);
  Wire.beginTransmission(COMPASS_ADRESS);
  Wire.write(0x00); //Sends the register we wish to start reading from
  Wire.write(0xF5);
  Wire.endTransmission();
  delay(20);
  Wire.beginTransmission(COMPASS_ADRESS);
  Wire.write(0x00); //Sends the register we wish to start reading from
  Wire.write(0xF6);
  Wire.endTransmission();
  delay(20);
}

void Compass::eraseCalibration()
{
  Wire.beginTransmission(COMPASS_ADRESS);
  Wire.write(0x00); //Sends the register we wish to start reading from
  Wire.write(0xE0);
  Wire.endTransmission();
  delay(20);
  Wire.beginTransmission(COMPASS_ADRESS);
  Wire.write(0x00); //Sends the register we wish to start reading from
  Wire.write(0xE5);
  Wire.endTransmission();
  delay(20);
  Wire.beginTransmission(COMPASS_ADRESS);
  Wire.write(0x00); //Sends the register we wish to start reading from
  Wire.write(0xE2);
  Wire.endTransmission();
  delay(20);
}

bool Compass::checkCalibration()
{
  Wire.beginTransmission(COMPASS_ADRESS);
  Wire.write(0x1E); //Sends the register we wish to start reading from
  Wire.endTransmission();
  Wire.requestFrom(COMPASS_ADRESS, 1);
  if (Wire.available() >= 1)
  {
    _checkCalibration = Wire.read();
  }
//Read byte and prints bits
  for (byte mask = 0x80; mask; mask >>= 1)
  {
    if (mask & _checkCalibration)
      Serial.print('1');
    else
      Serial.print('0');
  }

  Serial.println();

  return _checkCalibration;
}

int Compass::getTemperature()
{
  Wire.beginTransmission(COMPASS_ADRESS);
  Wire.write(0x18); //Sends the register we wish to start reading from
  Wire.endTransmission();
  Wire.requestFrom(COMPASS_ADRESS, 2);
  if (Wire.available() >= 2)
  {
    _high_byteTemp = Wire.read();
    _low_byteTemp = Wire.read();
    _temperature = _high_byteTemp;
    _temperature <<= 8;
    _temperature += _low_byteTemp;
  }

  return _temperature - 10; //-10 wegen eigentemperatur des sensors, ist ungefähr
}

unsigned char Compass::getAngle8() { return _angle8; }
int Compass::getAngle16() { return _angle16 / 10; }
int Compass::getPitch() { return _pitch; }
int Compass::getRoll() { return _roll; }