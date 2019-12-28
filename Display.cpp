#include "Display.h"

extern BallTouch ballTouch;
extern Chassis m;

/*******************************************************************
 * Example
 * ******************************************************************/

// You might need to change NexConfig.h file in your ITEADLIB_Arduino_Nextion folder
// Set the baudrate which is for debug and communicate with Nextion screen
NexText Display::_tLedState = NexText(2, 4, "t0");
NexButton Display::_bLedOn = NexButton(2, 5, "b1");
NexButton Display::_bLedOff = NexButton(2, 6, "b2");
NexSlider Display::_hLedSlider = NexSlider(2, 3, "h0");

//Calibrate BallTouch
NexButton Display::_ballTouchBall = NexButton(7, 3, "b1");
NexButton Display::_ballTouchNoBall = NexButton(7, 4, "b2");
NexButton Display::_ballTouchThreshold = NexButton(7, 5, "b3");
NexText Display::_ballTouchStatus = NexText(7, 6, "t0");

//Hardware BallTouch
NexText Display::_caliStatus = NexText(8, 3, "t0");
NexText Display::_ballStatus = NexText(8, 4, "t1");
NexTimer Display::_updateBallStatus = NexTimer(8,5,"tm0");

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
    //Example
    &_bLedOn,
    &_bLedOff,
    &_hLedSlider,

    //Cali BallTouch
    &_ballTouchBall,
    &_ballTouchNoBall,
    &_ballTouchThreshold,

    //Hardware BallTouch
    //attach _enKick

    //Hardware enable Disable
    &_enKick,
    &_enMotors,

    //Harware Kicker
    &_kickBall,
    &_enKick2,

    //Cali Kicker
    &_kickSlider,

    //Hardware Motors
    &_enMotors2,

    NULL};

/*******************************************************************
 * Example
 * ******************************************************************/
/*
 * Button _bLedOn component pop callback function. 
 * When the ON button is released, the LED turns on and the state text changes. 
 */
void Display::bLedOnPopCallback(void *ptr)
{
  _tLedState.setText("State: on");
  digitalWrite(_led1, HIGH);
}

/*
 * Button _bLedOff component pop callback function. 
 * When the OFF button is released, the LED turns off and the state text changes. 
 */
void Display::bLedOffPopCallback(void *ptr)
{
  _tLedState.setText("State: off");
  digitalWrite(_led1, LOW);
}

/*
 * Slider _hLedSlider component pop callback function. 
 * When the slider is released, the LED brightness changes and the slider text changes. 
 */
void Display::hLedSliderPopCallback(void *ptr)
{
  uint32_t number = 0;
  char temp[10] = {0};
  // change text with the current slider value
  _hLedSlider.getValue(&number);
  utoa(number, temp, 10);
  // change LED brightness
  analogWrite(_led1, number);
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
  calibrated = !caliNoBall || !caliBall ? false : true;
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
  Serial.println("switched");
  enKick = !enKick;
}

void Display::enMotors(void *ptr)
{
  m.setMotEn(!m.getMotEn());
}

void Display::updateEnPage(void *ptr)
{
  if (enKick)
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
  if (enKick)
    kick();
  else
  {
    enKick = true;
    kick();
    enKick = false;
  }

}

//Cali Kicker
void Display::kickSlider(void *ptr) {
    uint32_t number = 0;
  char temp[10] = {0};
  // change text with the current slider value
  _kickSlider.getValue(&number);
  utoa(number, temp, 10);
  kickPower = map(number, 0, 100, 100, 255);
  caliKick = true;
}

//Hardware Motors
//attach to enMotos






void Display::init() override
{
  nexInit(); // Register the pop event callback function of the components

  //Example
  _bLedOn.attachPop(bLedOnPopCallback, &_bLedOn);
  _bLedOff.attachPop(bLedOffPopCallback, &_bLedOff);
  _hLedSlider.attachPop(hLedSliderPopCallback);
  pinMode(_led1, OUTPUT);

  //Cali BallTouch
  _ballTouchBall.attachPop(ballTouchBall, &_ballTouchBall);
  _ballTouchNoBall.attachPop(ballTouchNoBall, &_ballTouchNoBall);
  _ballTouchThreshold.attachPop(ballTouchThreshold, &_ballTouchThreshold);

  //Hardware BallTouch
  _updateBallStatus.attachTimer(updateBallTimer, &_updateBallStatus);

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
}

void Display::update() override
{
  nexLoop(_nex_listen_list);
}
