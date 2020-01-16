#pragma once#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Pixy.h>

//#include <Nextion.h>

#include "Ultrasonic.h"
#include "Compass.h"
#include "Chassis.h"
#include "BallTouch.h"
#include "Utility.h"
#include "Camera.h"
#include "Pin.h"
#include "PUI.h"

/*****************************************************
  Fahren - Chassis
*****************************************************/
extern int drivePower, driveRotation, driveDirection, driveOrientation;

/*****************************************************
  Kick/Lightbarrier - Utility
*****************************************************/
extern unsigned long kickTimer;
extern bool hasBall;

/*****************************************************
  Camera 
*****************************************************/
#define SIG_BALL 1
#define SIG_GOAL 2
#define CAM_EN true

