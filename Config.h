#pragma once

#include "Arduino.h"
#include "Pin.h"

// Implementierung: FAHREN
extern int drivePower, driveRotation, driveDirection, driveOrientation;

// Implementierung: KICK, LIGHT_BARRIER
extern unsigned long kickTimer;
extern unsigned int kickPower;
extern bool enKick, caliKick;
extern bool hasBall, caliNoBall, caliBall, calibrated;
