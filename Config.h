#pragma once

#include "Arduino.h"
#include "Pin.h"
#include "EEPROM.h"


//Debugging
#define DEBUG               1

#define DEBUG_PLAYER        0    
#define DEBUG_COMPASS       0
#define DEBUG_CAMERA        0
#define DEBUG_CHASSIS       0
#define DEBUG_BLUETOOTH     0
#define DEBUG_ULTRASONIC    0
#define DEBUG_KICK          0
#define DEBUG_BALLTOUCH     0
#define DEBUG_DISPLAY       0
#define DEBUG_PUI           0
#define DEBUG_UTILITY       1



//Bluetooth
#define MSG_SIZE 3

//EEPROM
#define EEPROM_BALLTOUCH_THRESHOLD 0

#define HEARTBEAT_LOOPTIME 500

// PID-Regler
#define PID_FILTER_P 0.23   // [0 bis *]~.27 p:proportional
#define PID_FILTER_I 0.1 // [0 bis *]~.02 i:vorausschauend 
#define PID_FILTER_D 0.026  // [0 bis *]~.03 d:Schwung herausnehmen (nicht zu weit drehen)



#if DEBUG == 1 && DEBUG_PLAYER == 1
#   define LogPlayer(msg)   Serial.println("Player: " + (String)msg)
#else
#   define LogPlayer(msg)
#endif

#if DEBUG == 1 && DEBUG_COMPASS == 1
#   define LogCmps(msg)   Serial.println("Compass: " + (String)msg)
#else
#   define LogCmps(msg)
#endif

#if DEBUG == 1 && DEBUG_CAMERA == 1
#   define LogCam(msg)   Serial.println("Camera: " + (String)msg)
#else
#   define LogCam(msg)
#endif

#if DEBUG == 1 && DEBUG_CHASSIS == 1
#   define LogChassis(msg)   Serial.println("Chassis: " + (String)msg)
#else
#   define LogChassis(msg)
#endif

#if DEBUG == 1 && DEBUG_BLUETOOTH == 1
#   define LogBluetooth(msg)   Serial.println("Bluetooth: " + (String)msg)
#else
#   define LogBluetooth(msg)
#endif

#if DEBUG == 1 && DEBUG_ULTRASONIC == 1
#   define LogUs(msg)   Serial.println("Ultrasonic: " + (String)msg)
#else
#   define LogUs(msg)
#endif

#if DEBUG == 1 && DEBUG_KICK == 1
#   define LogKick(msg)   Serial.println("Kick: " + (String)msg)
#else
#   define LogKick(msg)
#endif

#if DEBUG == 1 && DEBUG_BALLTOUCH == 1
#   define LogBalltouch(msg)   Serial.println("Balltouch: " + (String)msg)
#else
#   define LogBalltouch(msg)
#endif

#if DEBUG == 1 && DEBUG_DISPLAY == 1
#   define LogDisplay(msg)   Serial.println("Display: " + (String)msg)
#else
#   define LogDisplay(msg)
#endif

#if DEBUG == 1 && DEBUG_PUI == 1
#   define LogPui(msg)   Serial.println("PUI: " + (String)msg)
#else
#   define LogPui(msg)
#endif

#if DEBUG == 1 && DEBUG_UTILITY == 1
#   define LogUtility(msg)   Serial.println("Utility: " + (String)msg)
#else
#   define LogUtility(msg)
#endif