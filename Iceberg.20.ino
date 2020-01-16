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

#include "Display.h"

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
unsigned int kickPower = 0;
bool caliKick = false;
bool enKick = false;

//Hardware hardwares[1] = {        us        };

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
  // for(Hardware hardware : hardwares)
  //   hardware.init();
  Display::init(); //static class maybe cannt init int foreach
  //us.init();
  //cmps.init();
Camera camera;
PUI pui;

  pui.init();
  camera.init();
  startSound();
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
  Display::update(); //maybe can implement it alltough its static class
  // for(Hardware hardware : hardwares)
  //   hardware.update();
  m.update();
  ballTouch.update();
  if (ballTouch.hasBall())
  {
    kick();
    startSound();
  }
  m.drive(0,50);
  // //Serial.println((String) ballTouch.getThreshold() + "  |  " + ballTouch.getBallThreshold() + "  |  " + ballTouch.getNoBallThreshold());
  // // cmps.update();
  // Serial.println((String)us.getFrontLeft() + " | " + us.getLeft() + " | " + us.getBack() + " | " + us.getRight() + " | " + us.getFrontRight());
  if(camera.getBPos() == 0){
    chassis.drive(0,-30,0);
  }else{
    chassis.drive(map(camera.getBPos(),0,320,90,-90),30,0);
  }
  camera.update();
}