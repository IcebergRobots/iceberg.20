// Einstellungen:
#include "Compass.h"

#include <Wire.h>

#define ANGLE_8  1           // Register to read 8bit angle from

unsigned char high_byte, low_byte, angle8;
char pitch, roll;
unsigned int angle16;
int richtung = 0;

Compass::Compass() {
  
}

void Compass::init() {
  Wire.beginTransmission(COMPASS_ADRESS);
  Wire.write(ANGLE_8);                     //Sends the register we wish to start reading from
  Wire.endTransmission();
}

void Compass::update() {
  

  // Request 5 bytes from the CMPS12
  // this will give us the 8 bit bearing,
  // both bytes of the 16 bit bearing, pitch and roll
  Wire.requestFrom(COMPASS_ADRESS, 5);

  while(Wire.available() < 5);        // Wait for all bytes to come back

  angle8 = Wire.read();               // Read back the 5 bytes
  high_byte = Wire.read();
  low_byte = Wire.read();
  pitch = Wire.read();
  roll = Wire.read();

  angle16 = high_byte;                 // Calculate 16 bit angle
  angle16 <<= 8;
  angle16 += low_byte;

  richtung = (float)angle16 / (float)10;
}

float Compass::getAngle() {
  return richtung;
}