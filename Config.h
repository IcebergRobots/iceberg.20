#pragma once

#include "Arduino.h"
#include "Pin.h"
#include "EEPROM.h"



//Bluetooth
#define BLUETOOTH true            // soll eine Bluetooth-Kommunikation bestehen?

//EEPROM
#define EEPROM_BALLTOUCH_THRESHOLD 0

#define HEARTBEAT_LOOPTIME 500

// PID-Regler
#define PID_FILTER_P 0.2   // [0 bis *]~.27 p:proportional
#define PID_FILTER_I 0  // [0 bis *]~0   i:vorausschauend
#define PID_FILTER_D 1  // [0 bis *]~.03 d:Schwung herausnehmen (nicht zu weit drehen)

//Camera 
#define SIG_BALL 1
#define SIG_GOAL 2