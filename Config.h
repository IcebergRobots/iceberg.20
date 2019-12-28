#include "Arduino.h"
#include "Wire.h"
#include "Nextion.h"

#include "Hardware.h"
#include "Pins.h"

#include "Ultrasonic.h"
#include "Compass.h"
#include "Chassis.h"
#include "BallTouch.h"
#include "Utility.h"
#include "Display.h"

// Implementierung: FAHREN
extern int drivePower, driveRotation, driveDirection, driveOrientation;

// Implementierung: KICK, LIGHT_BARRIER
extern unsigned long kickTimer;
extern unsigned int kickPower;
extern bool enKick, caliKick;
extern bool hasBall, caliNoBall, caliBall, calibrated;
