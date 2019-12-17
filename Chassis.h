#ifndef Chassis_h
#define Chassis_h

#include "Config.h"

#define FWD0            23
#define BWD0            25
#define PWM0            8

#define FWD1            27
#define BWD1            29
#define PWM1            9

#define FWD2            37
#define BWD2            35
#define PWM2            10

#define FWD3            33
#define BWD3            31
#define PWM3            11

#define M0_CURR         A1 //  Pin zum messen des Motorstroms von M1
#define M1_CURR         A2 //  Pin zum messen des Motorstroms von M2
#define M2_CURR         A3 //  Pin zum messen des Motorstroms von M3
#define M3_CURR         A4 //  Pin zum messen des Motorstroms von M4

class Chassis
{
  public:
    Chassis();
    Chassis(byte angle);

    void init();

    void setPins(byte id, byte fwd, byte bwd, byte pwm, int curSens);
    void setAngle(byte angle);

    void steerMotor(byte id, int power);

    void drive();
    void drive(int values[]);
    void drive(int angle, int power);
    void drive(int angle, int power, int rotation);

    void calculate(int angle, int power);
    void calculate(int angle, int power, int rotation);

    void brake(bool activ);

    void setMotEn(bool motEn);
    bool getMotEn();
    void switchMotEn();

  private:
    byte _fwd[4];    // digitaler PIN fuer Vorwaertsrotation
    byte _bwd[4];    // digitaler PIN fuer Rueckwaertsrotation
    byte _pwm[4];    // analoger PIN fuer Geschwindigkeit

    byte _curSens[4];

    int _values[4];  // Zwischenspeicher für Outputsignale

    byte _angle;
    bool _motEn;    // gibt an, ob die Motoren an sind
    bool _halfSpeed = false;

    int _curr;
};

#endif
