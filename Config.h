#pragma once

#include "Arduino.h"
#include "Pin.h"

/*****************************************************
  Fahren - Chassis
*****************************************************/
extern int drivePower, driveRotation, driveDirection, driveOrientation;

/*****************************************************
  Kick/Lightbarrier - Utility
*****************************************************/
extern unsigned long kickTimer;
extern unsigned int kickPower;
extern bool enKick, caliKick;
extern bool hasBall, caliNoBall, caliBall, calibrated;

/*****************************************************
  Camera 
*****************************************************/
#define SIG_BALL 1
#define SIG_GOAL 2
#define CAM_EN true

