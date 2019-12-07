#include "Arduino.h"
#include "Wire.h"
#include "Nextion.h"
#include "Ultrasonic.h"
#include "Compass.h"
#include "Chassis.h"

// Implementierung: FAHREN
extern bool start, onLine, isHeadstart, isAvoidMate, isKeeperLeft, wasMotor, wasStart;
extern int rotMulti, drivePower, driveRotation, driveDirection, driveOrientation, lineDir;
extern String driveState;