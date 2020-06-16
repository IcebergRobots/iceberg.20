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

Compass cmps(ENDISABLE_COMPASS);
Ultrasonic us(ENDISABLE_ULTRASONIC);
Pui pui(ENDISABLE_PUI);
BallTouch ballTouch(ENDISABLE_BALLTOUCH);
Chassis m(ENDISABLE_CHASSIS);
Camera camera(ENDISABLE_CAMERA);
Kick kick(ENDISABLE_KICK, 255);
Bluetooth bt(ENDISABLE_BLUETOOTH);
Bottom bottom(ENDISABLE_BOTTOM);

Hardware *hardwares[] = {&cmps, &us, &pui, &ballTouch, &m, &camera, &kick, &bt, &bottom};

Offense offense;
Defense defense;
Standby standby;

Player *player;

//Shared shared;


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

  chooseRobot();
  startSound();

  I2c.begin();
  I2c.timeOut(3000);
  I2c.pullup(true);
  // I2c.scan();


  // Display::init(); //static class maybe cant init int foreach
  for (Hardware *hardware : hardwares)
    hardware->init();

  player = &standby;

  //Debug
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

  if(PLAY)
  {
    player = player->update();
    player->play();
  }
// if(pui.button_compass)
//         cmps.cali();
//           Serial.println(cmps.getPIDOutput());

  
  // Display::update(); //maybe can implement it alltough its static class
  LogPlayer("Goal Rating: " + player->rateGoal() + "    Ball Rating: " + player->rateBall());
  //Debug
  LogBalltouch("Has sees Ball: " + ballTouch.hasBall());
  LogBottom("Sees line: " + bottom.seesLine());
  LogCmps("Angle" + cmps.getAngle() + "  Pitch: " + cmps.getPitch() + "  Roll: " + cmps.getRoll());
  LogUs("B: " + us.getBack() + "  R: " + us.getRight() + "  L: " + us.getLeft() + "  FL: " + us.getFrontLeft() + "  FR: " + us.getFrontRight());
}
