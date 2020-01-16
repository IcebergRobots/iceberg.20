#pragma once
// Motorpins:
#define NUM_OF_M        4

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


// BallTouchpins:
#define LED_PIN         47
#define SENSOR_PIN      A15

// KickerPins
#define KICKER          12
#define POTKICK         A0  //  hier ist das Potentiometer unten auf der Platine angeschlossen

//Tones
#define BUZZER          13

//Ultraadresses
//addresses of the Ultrasonicsensors named by their position
#define NUM_OF_US       5

#define FRONT_LEFT      112
#define LEFT            113
#define FRONT_RIGHT     116
#define BACK            114
#define RIGHT           115
