#include "Display.h"

extern BallTouch ballTouch;
extern Chassis m;
extern Kick kick;

// You might need to change NexConfig.h file in your ITEADLIB_Arduino_Nextion folder
// Set the baudrate which is for debug and communicate with Nextion screen

//Overview
NexButton Display::_goRAM = NexButton(2, 3, "b1");

//Overview FreeRAM
NexNumber Display::_freeRAM = NexNumber(13, 3, "freeram");


//Calibrate BallTouch
NexButton Display::_ballTouchBall = NexButton(7, 3, "b1");
NexButton Display::_ballTouchNoBall = NexButton(7, 4, "b2");
NexButton Display::_ballTouchThreshold = NexButton(7, 5, "b3");
NexText Display::_ballTouchStatus = NexText(7, 6, "t0");

//Hardware BallTouch
NexText Display::_ballStatus = NexText(8, 4, "t1");
NexPage Display::_updateBallStatus = NexPage(8,0,"hardBalltouch");

//Hardware Enable Disable
NexDSButton Display::_enKick = NexDSButton(9, 3, "kicken");
NexDSButton Display::_enMotors = NexDSButton(9, 6, "motorsen");
NexPage Display::_updateEnPage = NexPage(9, 0, "endisable");

//Hardware Kicker
NexButton Display::_kickBall = NexButton(10, 3, "b1");
NexDSButton Display::_enKick2 = NexDSButton(10, 4, "kicken");

//Cali Kicker
NexButton Display::_kickBall2 = NexButton(11, 4, "b1");
NexSlider Display::_kickSlider = NexSlider(11,1,"h0");

//Harware Motors
NexDSButton Display::_enMotors2 = NexDSButton(12, 4, "motorsen");

NexTouch *Display::_nex_listen_list[NUM_OBJECTS] = {

    //Overview
    &_goRAM,
    //Cali BallTouch
    &_ballTouchBall,
    &_ballTouchNoBall,
    &_ballTouchThreshold,

    //Hardware BallTouch
    &_updateBallStatus,

    //Hardware enable Disable
    &_enKick,
    &_enMotors,

    //Harware Kicker
    &_kickBall,
    &_enKick2,

    //Cali Kicker
    &_kickSlider,
    &_kickBall2,

    //Hardware Motors
    &_enMotors2,

    NULL};

//Overview
void Display::goRAM(void *ptr)
{
  _freeRAM.setValue(getFreeSRAM());
}

//Calibrate BallTouch
void Display::ballTouchBall(void *ptr)
{
  ballTouch.calibrateBall();
}

void Display::ballTouchNoBall(void *ptr)
{
  ballTouch.calibrateNoBall();
}

void Display::ballTouchThreshold(void *ptr)
{
  ballTouch.calculateTreshold();
}

//Hardware BallTouch
void Display::updateBallTimer(void *ptr) {
  if (ballTouch.hasBall())
    _ballStatus.setText("Yes");
    else
    _ballStatus.setText("No");
}

//Hardware Enable/Disable
void Display::switchEnKick(void *ptr)
{
  kick.setEn(!kick.getEn());
}

void Display::enMotors(void *ptr)
{
  m.setMotEn(!m.getMotEn());
}

void Display::updateEnPage(void *ptr)
{
  if (kick.getEn())
    _enKick.setValue(1);
  else
    _enKick.setValue(0);

  if (m.getMotEn())
    _enMotors.setValue(1);
  else
    _enMotors.setValue(0);
}

//Hardware Kicker
void Display::kickBall(void *ptr) {
  if (kick.getEn())
    kick.kick();
  else
  {
    kick.setEn(true);
    kick.kick();
    kick.setEn(false);
  }

}

//Cali Kicker
void Display::kickSlider(void *ptr) {
    uint32_t number = 0;
  char temp[10] = {0};
  // change text with the current slider value
  _kickSlider.getValue(&number);
  utoa(number, temp, 10);
  kick.setPower(map(number, 0, 100, 100, 255));
}

//Hardware Motors
//attach to enMotos






void Display::init()
{
  nexInit(); // Register the pop event callback function of the components

  //Overview
  _goRAM.attachPop(goRAM, &_goRAM);

  //Cali BallTouch
  _ballTouchBall.attachPop(ballTouchBall, &_ballTouchBall);
  _ballTouchNoBall.attachPop(ballTouchNoBall, &_ballTouchNoBall);
  _ballTouchThreshold.attachPop(ballTouchThreshold, &_ballTouchThreshold);

  //Hardware BallTouch
  _updateBallStatus.attachPop(updateBallTimer, &_updateBallStatus);

  //Hardware Enable/Disable
  _enKick.attachPop(switchEnKick, &_enKick);
  _enMotors.attachPop(enMotors, &_enMotors);
  _updateEnPage.attachPop(updateEnPage, &_updateEnPage);

  //Hardware Kicker
  _kickBall.attachPop(kickBall, &_kickBall);
  _enKick2.attachPop(switchEnKick, &_enKick2);

  //Cali Kicker
  _kickBall2.attachPop(kickBall, &_kickBall2);
  _kickSlider.attachPop(kickSlider, &_kickSlider);

  //Hardware Motors
  _enMotors2.attachPop(enMotors, &_enMotors2);
  LogDisplay("Initilized");
}

void Display::update()
{
  nexLoop(_nex_listen_list);
}
