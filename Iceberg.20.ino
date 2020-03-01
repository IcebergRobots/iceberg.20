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
Kick kick(true, 260);
Bluetooth bt(false);
Bottom bottom(true);

Hardware *hardwares[] = {&cmps, &us, &pui, &ballTouch, &m, &camera, &kick, &bt, &bottom};

Offense offense;
Defense defense;
Standby standby;

Player *player;

int robot;
bool headstart;
unsigned long headstartTimer;

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
  Serial3.begin(115200);
  Serial.begin(9600);

  pinMode(HARDWARE_DIFFERENCE, INPUT_PULLUP);
  if(digitalRead(HARDWARE_DIFFERENCE) == HIGH)
    robot = 1;                                  // RObot A
  else
    robot = 0;                                    //RObot B

  I2c.begin();
  I2c.timeOut(3000);
  I2c.pullup(true);
  // I2c.scan();
  startSound();

  // Display::init(); //static class maybe cant init int foreach
  for (Hardware *hardware : hardwares)
    hardware->init();

  // if(robot == 1)
  //   player = &defense;
  // else
  //   player = &offense;
  player = &standby;
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

  
  // Serial.println(bottom.getAngel());
  
  player = player->update();
  player->play();
  Serial.println(pui.switch_headstart);
  
  // Serial.println(bottom.getAngel());
  // LogUs("B: " + us.getBack() + "  R: " + us.getRight() + "  L: " + us.getLeft() + "  FL: " + us.getFrontLeft() + "  FR: " + us.getFrontRight());
  // Display::update(); //maybe can implement it alltough its static class
}