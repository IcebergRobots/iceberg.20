/*
 ______________________________________________________________________________
|                                                                              |    
|  8888888 .d8888b.  8888888888 888888b.   8888888888 8888888b.   .d8888b.     |
|    888  d88P  Y88b 888        888  "88b  888        888   Y88b d88P  Y88b    |
|    888  888    888 888        888  .88P  888        888    888 888    888    |
|    888  888        8888888    8888888K.  8888888    888   d88P 888           |
|    888  888        888        888  "Y88b 888        8888888P"  888  88888    |
|    888  888    888 888        888    888 888        888 T88b   888    888    |
|    888  Y88b  d88P 888        888   d88P 888        888  T88b  Y88b  d88P    |
|  8888888 "Y8888P"  8888888888 8888888P"  8888888888 888   T88b  "Y8888P88    |
|                                                                              |
|                                                                              |
|                                                                              |
|  8888888b.   .d88888b.  888888b.    .d88888b. 88888888888 .d8888b.           |
|  888   Y88b d88P" "Y88b 888  "88b  d88P" "Y88b    888    d88P  Y88b          |
|  888    888 888     888 888  .88P  888     888    888    Y88b.               |
|  888   d88P 888     888 8888888K.  888     888    888     "Y888b.            |
|  8888888P"  888     888 888  "Y88b 888     888    888        "Y88b.          |
|  888 T88b   888     888 888    888 888     888    888          "888          |
|  888  T88b  Y88b. .d88P 888   d88P Y88b. .d88P    888    Y88b  d88P          |
|  888   T88b  "Y88888P"  8888888P"   "Y88888P"     888     "Y8888P"           |
|                                                                              |     
|______________________________________________________________________________|

*/

#include "Config.h"
Ultrasonic us;

Compass cmps;

Chassis m;
int drivePower = 0;       // [-255 bis 255] aktuelle maximale Motorstärke
int driveRotation = 0;    // [-255 bis 255] aktuelle Rotationsstärke
int driveDirection = 0;   // [-180 bis 180] Ziel-Fahrrichtung
int driveOrientation = 0; // [-180 bis 180] Ziel-Orientierungswinkel


BallTouch ballTouch;
bool calibrated = false;
bool caliNoBall = false;
bool caliBall = false;

unsigned long kickTimer = 0;
bool enKick = false;


//###################################################################################################
//##                                                                                               ##
//##    ####   ######  ######  ##  ##  #####                                                       ##
//##   ##      ##        ##    ##  ##  ##  ##                                                      ##
//##    ####   ####      ##    ##  ##  #####                                                       ##
//##       ##  ##        ##    ##  ##  ##                                                          ##
//##    ####   ######    ##     ####   ##                                                          ##
//##                                                                                               ##
//###################################################################################################


void setup()
{
  Serial.begin(9600);
  Wire.begin();
  ballTouch.init();
  m.init();
  startSound();
  Display::init();
  //us.init();
  //cmps.init();
}

//###################################################################################################
//##...............................................................................................##
//##....##.......####....####...#####..............................................................##
//##....##......##..##..##..##..##..##.............................................................##
//##....##......##..##..##..##..#####..............................................................##
//##....##......##..##..##..##..##.................................................................##
//##....######...####....####...##.................................................................##
//##...............................................................................................##
//###################################################################################################

void loop()
{
  Display::update();
  // us.update();
  ballTouch.update();
  
   if (ballTouch.hasBall())
   {
     kick();
    startSound();
    Serial.println("yo");
  }
  // //Serial.println((String) ballTouch.getThreshold() + "  |  " + ballTouch.getBallThreshold() + "  |  " + ballTouch.getNoBallThreshold());
  m.drive(0, 40);
  // // cmps.update();
  // Serial.println((String)us.getFrontLeft() + " | " + us.getLeft() + " | " + us.getBack() + " | " + us.getRight() + " | " + us.getFrontRight());
}