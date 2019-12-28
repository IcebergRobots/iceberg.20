#include "Arduino.h"
#include "Wire.h"
#include "Nextion.h"

#include "Hardware.h"
#include "Ultrasonic.h"
#include "Compass.h"
#include "Chassis.h"
#include "BallTouch.h"
#include "Utility.h"
#include "Display.h"

#include "Pins.h"

// Implementierung: FAHREN
extern int drivePower, driveRotation, driveDirection, driveOrientation;

// Implementierung: KICK, LIGHT_BARRIER
extern unsigned long kickTimer;
extern unsigned int kickPower;
extern bool enKick, caliKick;
extern bool hasBall, caliNoBall, caliBall, calibrated;
