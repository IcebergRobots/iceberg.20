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

#include "Offense.h"
#include "Defense.h"
#include "Standby.h"

Compass cmps(true);
Ultrasonic us(true);
Pui pui(true);
BallTouch ballTouch(true);
Chassis m(true);
Camera camera(true);
Kick kick(true, 240);
Bluetooth bt(false);
Bottom bottom(true);

Hardware *hardwares[] = {&cmps, &us, &pui, &ballTouch, &m, &camera, &kick, &bt, &bottom};

Offense offense;
Defense defense;
Standby standby;

Player *player;

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
  startSound();

  // Display::init(); //static class maybe cant init int foreach
  for (Hardware *hardware : hardwares)
    hardware->init();

  player = &standby;
  player->initPID();

  LogCmps(cmps.checkCalibration());
  LogUtility("free SRAM: " + getFreeSRAM());
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

unsigned long testtime;
void loop()
{
  heartbeat();

  for (Hardware *hardware : hardwares)
    hardware->update();

  // if(pui.button_compass)
  // {
  //   cmps.cali();
  // }
  // Serial.println(cmps.getAngle());
    // if(pui.button_kick)
    //   kick.kick();
  // Serial.println(cmps.checkCalibration());
  Serial.println(cmps.getAngle());
  player = player->update();
  player->play();
  // player->updatePID();
  // m.drive(0,0, player->getPIDOutput());
  // LogUs("B: " + us.getBack() + "  R: " + us.getRight() + "  L: " + us.getLeft() + "  FL: " + us.getFrontLeft() + "  FR: " + us.getFrontRight());
  
  // Display::update(); //maybe can implement it alltough its static class
}