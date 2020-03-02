#include "Chassis.h"

// array auslesen ist schneller als berechnen
const int sinus[360] = {0, 175, 349, 523, 698, 872, 1045, 1219, 1392, 1564, 1736, 1908, 2079, 2250, 2419, 2588, 2756, 2924, 3090, 3256, 3420, 3584, 3746, 3907, 4067, 4226, 4384, 4540, 4695, 4848, 5000, 5150, 5299, 5446, 5592, 5736, 5878, 6018, 6157, 6293, 6428, 6561, 6691, 6820, 6947, 7071, 7193, 7314, 7431, 7547, 7660, 7771, 7880, 7986, 8090, 8192, 8290, 8387, 8480, 8572, 8660, 8746, 8829, 8910, 8988, 9063, 9135, 9205, 9272, 9336, 9397, 9455, 9511, 9563, 9613, 9659, 9703, 9744, 9781, 9816, 9848, 9877, 9903, 9925, 9945, 9962, 9976, 9986, 9994, 9998, 10000, 9998, 9994, 9986, 9976, 9962, 9945, 9925, 9903, 9877, 9848, 9816, 9781, 9744, 9703, 9659, 9613, 9563, 9511, 9455, 9397, 9336, 9272, 9205, 9135, 9063, 8988, 8910, 8829, 8746, 8660, 8572, 8480, 8387, 8290, 8192, 8090, 7986, 7880, 7771, 7660, 7547, 7431, 7314, 7193, 7071, 6947, 6820, 6691, 6561, 6428, 6293, 6157, 6018, 5878, 5736, 5592, 5446, 5299, 5150, 5000, 4848, 4695, 4540, 4384, 4226, 4067, 3907, 3746, 3584, 3420, 3256, 3090, 2924, 2756, 2588, 2419, 2250, 2079, 1908, 1736, 1564, 1392, 1219, 1045, 872, 698, 523, 349, 175, 0, -175, -349, -523, -698, -872, -1045, -1219, -1392, -1564, -1736, -1908, -2079, -2250, -2419, -2588, -2756, -2924, -3090, -3256, -3420, -3584, -3746, -3907, -4067, -4226, -4384, -4540, -4695, -4848, -5000, -5150, -5299, -5446, -5592, -5736, -5878, -6018, -6157, -6293, -6428, -6561, -6691, -6820, -6947, -7071, -7193, -7314, -7431, -7547, -7660, -7771, -7880, -7986, -8090, -8192, -8290, -8387, -8480, -8572, -8660, -8746, -8829, -8910, -8988, -9063, -9135, -9205, -9272, -9336, -9397, -9455, -9511, -9563, -9613, -9659, -9703, -9744, -9781, -9816, -9848, -9877, -9903, -9925, -9945, -9962, -9976, -9986, -9994, -9998, -10000, -9998, -9994, -9986, -9976, -9962, -9945, -9925, -9903, -9877, -9848, -9816, -9781, -9744, -9703, -9659, -9613, -9563, -9511, -9455, -9397, -9336, -9272, -9205, -9135, -9063, -8988, -8910, -8829, -8746, -8660, -8572, -8480, -8387, -8290, -8192, -8090, -7986, -7880, -7771, -7660, -7547, -7431, -7314, -7193, -7071, -6947, -6820, -6691, -6561, -6428, -6293, -6157, -6018, -5878, -5736, -5592, -5446, -5299, -5150, -5000, -4848, -4695, -4540, -4384, -4226, -4067, -3907, -3746, -3584, -3420, -3256, -3090, -2924, -2756, -2588, -2419, -2250, -2079, -1908, -1736, -1564, -1392, -1219, -1045, -872, -698, -523, -349, -175};

Chassis::Chassis(const bool& motEn)
{
  setMotEn(motEn);
}

void Chassis::init()
{
  if (getMotEn())
  {
    LogChassis("enabled");
    motors[0] = Motor(FWD0, BWD0, PWM0, M0_CURR);
    motors[1] = Motor(FWD1, BWD1, PWM1, M1_CURR);
    motors[2] = Motor(FWD2, BWD2, PWM2, M2_CURR);
    motors[3] = Motor(FWD3, BWD3, PWM3, M3_CURR);
    for (int i = 0; i < 4; i++)
    {
      motors[i].init();
    }
  } else  
    LogChassis("disabled");
  LogChassis("Initilized");
}

void Chassis::update()
{
  if (getMotEn())
  {
    /* code */
  }
  //TODO
}

/*****************************************************
  fahre mit Geschwindigkeit, Zielwinkel und Eigenrotation
  @param (optional) angle [-180 bis 180]: Zielwinkel
  @param (optional) power [-255 bis 255]: Geschwindigkeit
  @param (optional) rotation [-255 bis 255]: Eigenrotation -> Korrekturdrehung, um wieder zum Gegnertor ausgerichtet zu sein

  Winkel:0
      .--.
  90 /    \ -90
     \    /
      '--'
*****************************************************/
void Chassis::drive(int angle, int power, int rotation)
{
  calculate(angle, power, rotation);
  drive();
}
/*****************************************************
  steuere die Motoren an, um zu fahren
  @param _value: Zwischenspeicher
  - nutze Berechnungen des Zwischenspeichers
*****************************************************/
void Chassis::drive()
{
  if (getMotEn())
  {
    for (int i = 0; i < 4; i++)
    {
      motors[i].steerMotor();
    }
  }
}

/*****************************************************
  berechne Zwischenspeicher für Motoransteuerung
  @param angle [180 bis 180]: Zielwinkel
  @param power [-255 bis 255]: Geschwindigkeit
  @param (optional) rotation [-255 bis 255]: Eigenrotation -> Korrekturdrehung, um wieder zum Gegnertor ausgerichtet zu sein
*****************************************************/
void Chassis::calculate(int angle, int power, int rotation)
{

  if (power < 0)
  {                 //bei negativen Geschwindigkeiten,
    power = -power; //positive Geschwindigkeit
    angle += 180;   //bei 180° Drehung verwenden
  }

  power = constrain(power, 0, 255);

  while (angle < 0)
  {               //Eingabekorrektur
    angle += 360; //
  }               //
  angle %= 360;   //

  if (power + abs(rotation) > 255)
  {                                         //Wenn die Gesamtgeschwindigkeit zu groß ist,
    power -= (power + abs(rotation)) - 255; //wird die Geschwindigkeit ausreichend reduziert
  }

  //                                                      IDs:  .--.
  int sinA02 = sinus[(((ANGLE / 2) - angle) + 360) % 360]; //berechne Zwischenwert für Achse der Motoren 1 und 3      3 /    \ 0
  int sinA13 = sinus[(((ANGLE / 2) + angle) + 360) % 360]; //berechne Zwischenwert für Achse der Motoren 2 und 4      2 \    / 1
  //                                                            '--'
  int axis02 = power * (double)sinA02 / 10000; //berechne Motorstärken für Achse 1&3
  int axis13 = power * (double)sinA13 / 10000; //berechne Motorstärken für Achse 2&4

  motors[0].setPower(axis02 - rotation); //erstelle Zwischenspeicher für alle Motorstärken
  motors[1].setPower(axis13 - rotation);
  motors[2].setPower(axis02 + rotation);
  motors[3].setPower(axis13 + rotation);
}

void Chassis::headstart()
{
  if(getEn() && millis() - headstartTimer <= 500)
  {
      // for (int i = 0; i < 4; i++)
      // {
      //   motors[i].setPower(255);
      //   motors[i].steerMotor();
      // }
      drive(0, 255);
  }
}

/*****************************************************
  bremse aktiv oder passiv alle Motoren
  @param activ: aktives Bremsen?
*****************************************************/
void Chassis::brake(const bool& activ)
{
  for (byte i = 0; i < 4; i++)
  {
    motors[i].brake(activ);
  }
}

void Chassis::setMotEn(const bool& motEn)
{
  if(!motEn)
    brake(false);
  for (int i = 0; i < 4; i++)
  {
    motors[i].setEn(motEn);
  }
  _motEn = motEn;
}

const bool Chassis::getMotEn()
{
  return _motEn;
}
