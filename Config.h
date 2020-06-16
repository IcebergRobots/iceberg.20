#pragma once

#include "Arduino.h"
#include "Pin.h"
#include "EEPROM.h"

//En/Disabling hardware Components
#define ENDISABLE_COMPASS       1
#define ENDISABLE_CAMERA        1
#define ENDISABLE_CHASSIS       1
#define ENDISABLE_BLUETOOTH     0
#define ENDISABLE_ULTRASONIC    1
#define ENDISABLE_KICK          0
#define ENDISABLE_BALLTOUCH     0
#define ENDISABLE_PUI           1
#define ENDISABLE_BOTTOM        0

//Let the Robot Play
#define PLAY                    0

//Debugging
#define DEBUG                   1

#define DEBUG_PLAYER            1
#define DEBUG_COMPASS           0
#define DEBUG_COMPASS           0
#define DEBUG_CAMERA            0
#define DEBUG_CHASSIS           0
#define DEBUG_BLUETOOTH         0
#define DEBUG_ULTRASONIC        0
#define DEBUG_KICK              0
#define DEBUG_BALLTOUCH         0
#define DEBUG_BOTTOM            0
#define DEBUG_DISPLAY           0
#define DEBUG_PUI               0
#define DEBUG_UTILITY           1


#define SPIELGESCHWINDIGKEIT 50

//Rateing   weights in % sum should equal 100%
#define RATE_BALL_WEIGHT    20
#define RATE_GOAL_WEIGHT    80

//EEPROM
#define EEPROM_BALLTOUCH_THRESHOLD 0

//PLayerstates
#define STATE_STANDBY 0
#define STATE_OFFENSE 1
#define STATE_DEFENSE 2



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

#if DEBUG == 1 && DEBUG_BOTTOM == 1
#   define LogBottom(msg)   Serial.println("Balltouch: " + (String)msg)
#else
#   define LogBottom(msg)
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
