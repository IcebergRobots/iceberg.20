// Einstellungen:
#include "Compass.h"

void Compass::init()
{
  if (getEn())
  {
     if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
    // update();
    //firstCali();
    _myPID.SetMode(AUTOMATIC);
    // konfiguriere PID-Regler
    _myPID.SetTunings(PID_FILTER_P, PID_FILTER_I, PID_FILTER_D);
    _myPID.SetOutputLimits(-255, 255);
    LogCmps("enabled");
    LogCmps("Calibrated");
  }
  else
    LogCmps("disabled");
}

void Compass::update()
{
  if (getEn())
  {
   
  mag.getEvent(&mag_event);
  if (dof.magGetOrientation(SENSOR_AXIS_Z, &mag_event, &orientation))
  {
    /* 'orientation' should have valid .heading data now */
    _tmpAngle = orientation.heading;

    _median[0] = _median[1];
    _median[1] = _median[2];
    _median[2] = _tmpAngle;
    
    if(_median[0] > _median[1] && _median[0] < _median[2])
      _angle = _median[0];
    else if(_median[1] > _median[0] && _median[1] < _median[2])
      _angle = _median[1];
    else
      _angle = _median[2];
  }

    //old
    // I2c.write(COMPASS_ADRESS, 0x01); //Sends the register we wish to start reading from
    
    // // Request 5 bytes from the CMPS12
    // // this will give us the 8 bit bearing,
    // // both bytes of the 16 bit bearing, pitch and roll
    // I2c.read(COMPASS_ADRESS, 5);

    // if (I2c.available() >= 5)
    // {
    //   _angle8 = I2c.receive(); // Read back the 5 bytes
    //   _high_byte = I2c.receive();
    //   _low_byte = I2c.receive();
    //   _pitch = I2c.receive();
    //   _roll = I2c.receive();

    //   _angle16 = _high_byte; // Calculate 16 bit angle
    //   _angle16 <<= 8;
    //   _angle16 += _low_byte;
    // }
    // _input = -((getAngle() + 180) % 360 - 180);
    // _myPID.Compute();
  }
}

int Compass::getAngle()
{
   return (_angle - _offset + 180) % 360 -180;
}

int Compass::getPIDOutput()
{
    return constrain(getAngle() * PID_FILTER_P, -90, 90);
}

//old
// void Compass::firstCali()
// {
//   LogCmps("calibrated");
//   if(getAngle() != 0)
//     _firstOffset = getAngle();
// }

void Compass::cali()
{
  // _input = 0;
  update();
  LogCmps("recalibrated");
  _offset = _angle;
  
}

// void Compass::storeCalibration()
// {
//   if (getEn())
//   {
    
//     I2c.write(COMPASS_ADRESS, 0x00, 0xF0); //Sends the register we wish to start reading from
//     delay(20);

//     I2c.write(COMPASS_ADRESS, 0x00, 0xF5); //Sends the register we wish to start reading from
//     delay(20);

//     I2c.write(COMPASS_ADRESS, 0x00, 0xF6); //Sends the register we wish to start reading from
//     delay(20);
//   }
// }

// void Compass::eraseCalibration()
// {
//   if (getEn())
//   {
    
//     I2c.write(COMPASS_ADRESS, 0x00, 0xE0); //Sends the register we wish to start reading from
//     delay(20);

//     I2c.write(COMPASS_ADRESS, 0x00, 0xE5); //Sends the register we wish to start reading from
//     delay(20);

//     I2c.write(COMPASS_ADRESS, 0x00, 0xE2); //Sends the register we wish to start reading from
//     delay(20);
//   }
// }

// void Compass::checkCalibration()
// {
//   if (getEn())
//   {
//     I2c.write(COMPASS_ADRESS, 0x1E); //Sends the register we wish to start reading from
    
//     I2c.read(COMPASS_ADRESS, 1);
//     if (I2c.available() >= 1)
//     {
//       _checkCalibration = I2c.receive();
//     }
//     //Read byte and prints bits
//     byte bits = 0;
//     for (byte mask = 0x80; mask; mask >>= 1)
//     {
//       if (mask & _checkCalibration)
//         bits++; // Serial.print('1');
//       else
//       {
//         // Serial.print('0'); 
//       }      
//     }
//     if (bits == 8)
//     {
//       LogCmps("Succesfully calibrated");
//       digitalWrite(LED_BACK_LEFT, HIGH);
//       calibrated = true;
//     }
//   }
// }

// int Compass::getTemperature()
// {
//   if (getEn())
//   {
//     I2c.write(COMPASS_ADRESS, 0x18); //Sends the register we wish to start reading from
    
//     I2c.read(COMPASS_ADRESS, 2);
//     if (I2c.available() >= 2)
//     {
//       _high_byteTemp = I2c.receive();
//       _low_byteTemp = I2c.receive();
//       _temperature = _high_byteTemp;
//       _temperature <<= 8;
//       _temperature += _low_byteTemp;
//     }

//     return _temperature - 10; //-10 wegen eigentemperatur des sensors, ist ungefähr
//   }
//   return -1;
// }

// int Compass::getAngle()
// {
//   return (_angle16 / 10 - _firstOffset - _offset) % 360;
// }

// unsigned char Compass::getAngle8() { return _angle8; }
// int Compass::getAngle16() { return _angle16; }
// int Compass::getPitch() { return _pitch; }
// int Compass::getRoll() { return _roll; }