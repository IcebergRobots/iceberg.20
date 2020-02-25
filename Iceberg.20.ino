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
Bluetooth bt(true);

Hardware *hardwares[] = {&cmps, &us, &pui, &ballTouch, &m, &camera, &kick, &bt};

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

  Display::init(); //static class maybe cant init int foreach
  for (Hardware *hardware : hardwares)
    hardware->init();

  player = &offense;
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

void loop()
{
  heartbeat();
  for (Hardware *hardware : hardwares)
    hardware->update();

  player->updatePID();
  player = player->update();
  player->play();
  // Serial.println(player->rateGoal());
  // Serial.println("Hallo");

  LogUs("B: " + us.getBack() + "  R: " + us.getRight() + "  L: " + us.getLeft());
  
  Display::update(); //maybe can implement it alltough its static class
}