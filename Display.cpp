#include "Display.h"

extern Compass cmps;
extern Ultrasonic us;
extern Pui pui;
extern BallTouch ballTouch;
extern Chassis m;
extern Camera camera;
extern Kick kick;
extern Bluetooth bt;

extern Player *player;


// You might need to change NexConfig.h file in your ITEADLIB_Arduino_Nextion folder
// Set the baudrate which is for debug and communicate with Nextion screen

//Overview
NexButton Display::_goRAM = NexButton(2, 3, "b1");
NexButton Display::_goState = NexButton(2 ,4, "b2");

//Hardware
NexButton Display::_goHardBallt = NexButton(3 ,3, "b1");
NexButton Display::_goHardKick = NexButton(3 ,4, "b2");
NexButton Display::_goHardChassis = NexButton(3 ,5, "b3");

//Config
NexButton Display::_goEnDisable = NexButton(4 ,4, "b2");

//Config calibrate
NexButton Display::_goCaliKick = NexButton(6 ,4, "b2");

//Calibrate BallTouch
bool Display::_caliBall = false;
bool Display::_caliNoBall = false;
NexButton Display::_ballTouchBall = NexButton(7, 3, "b1");
NexButton Display::_ballTouchNoBall = NexButton(7, 4, "b2");
NexButton Display::_ballTouchThreshold = NexButton(7, 5, "b3");
NexText Display::_ballTouchStatus = NexText(7, 6, "t0");

//Hardware BallTouch
NexText Display::_ballCali = NexText(8, 3, "ballCali");
NexText Display::_ballStatus = NexText(8, 4, "t1");
NexText Display::_ballText = NexText(8, 5, "t0");

//Hardware Enable Disable
NexDSButton Display::_enKick = NexDSButton(9, 3, "kicken");
NexDSButton Display::_enChassis = NexDSButton(9, 6, "chassisen");
NexDSButton Display::_enCmps = NexDSButton(9, 7, "cmpsen");
NexDSButton Display::_enCam = NexDSButton(9, 10, "camen");
NexDSButton Display::_enUs = NexDSButton(9, 11, "usen");
NexDSButton Display::_enBallt = NexDSButton(9, 14, "ballten");
NexDSButton Display::_enBt = NexDSButton(9, 15, "bten");
NexDSButton Display::_enPui = NexDSButton(9, 18, "puien");


//Hardware Kicker
NexButton Display::_kickBall = NexButton(10, 3, "b1");
NexDSButton Display::_enKick2 = NexDSButton(10, 4, "kicken");

//Cali Kicker
NexButton Display::_kickBall2 = NexButton(11, 4, "b1");
NexSlider Display::_kickSlider = NexSlider(11,1,"h0");
NexNumber Display::_kickPower = NexNumber(11,3,"n0");

//Harware Chassis
NexDSButton Display::_enChassis2 = NexDSButton(12, 4, "chassisen");

//Overview FreeRAM
NexNumber Display::_freeRAM = NexNumber(13, 3, "freeram");

//Overview State
NexText Display::_state = NexText(14, 2, "tstate");


NexTouch *Display::_nex_listen_list[NUM_OBJECTS] = {

    //Overview
    &_goRAM,
    &_goState,

    //Hardware
    &_goHardBallt,
    &_goHardKick,
    &_goHardChassis,

    //Config
    &_goEnDisable,

    //Conifg Calibrate
    &_goCaliKick,

    //Cali BallTouch
    &_ballTouchBall,
    &_ballTouchNoBall,
    &_ballTouchThreshold,

    //Hardware BallTouch

    //Hardware enable Disable
    &_enKick,
    &_enChassis,
    &_enCmps,
    &_enCam,
    &_enUs,
    &_enBallt,
    &_enBt, 
    &_enPui,

    //Harware Kicker
    &_kickBall,
    &_enKick2,

    //Cali Kicker
    &_kickSlider,
    &_kickBall2,

    //Hardware Chassis
    &_enChassis2,

    NULL};

//Overview
void Display::goRAM(void *ptr)
{
  _freeRAM.setValue(getFreeSRAM());
}

void Display::goState(void *ptr)
{
  if(Player::currentState == STATE_STANDBY)
    _state.setText("Standby");
  else if(Player::currentState == STATE_OFFENSE)
    _state.setText("Offense");
  else if(Player::currentState == STATE_DEFENSE)
    _state.setText("Defense");
}

//Hardware
void Display::goHardBallt(void *ptr)
{
  //TODO
  if(ballTouch.getCali())
  {
    _ballCali.setText("Calibrated");
    if(ballTouch.getEn())
    {
      _ballText.setText("Sees Ball?");
      if(ballTouch.hasBall())
        _ballStatus.setText("Yes");
      else
        _ballStatus.setText("No");
    }
    else
      _ballText.setText("Disabled");
  }

}

void Display::goHardKick(void *ptr)
{
  if(kick.getEn())
    _enKick2.setValue(1);
  else
    _enKick2.setValue(0); 
}

void Display::goHardChassis(void *ptr)
{
  if(m.getMotEn())
    _enChassis2.setValue(1);
  else
    _enChassis2.setValue(0); 
}

//Config
void Display::goEnDisable(void *ptr)
{
  if(kick.getEn())
    _enKick.setValue(1);
  else
    _enKick.setValue(0);
  
  if(m.getMotEn())
    _enChassis.setValue(1);
  else
    _enChassis.setValue(0);

  if(cmps.getEn())
    _enCmps.setValue(1);
  else
    _enCmps.setValue(0);
  
  if(camera.getEn())
    _enCam.setValue(1);
  else
    _enCam.setValue(0);
  
  if(us.getEn())
    _enUs.setValue(1);
  else
    _enUs.setValue(0);

  if(ballTouch.getEn())
    _enBallt.setValue(1);
  else
    _enBallt.setValue(0);

  if(bt.getEn())
    _enBt.setValue(1);
  else
    _enBt.setValue(0);
  
  if(pui.getEn())
    _enPui.setValue(1);
  else
    _enPui.setValue(0);
}

//Configcalibrate
void Display::goCaliKick(void *ptr)
{
  _kickPower.setValue(map(kick.getPower(), 70, 255, 0, 100)+1); //+1 wegen irgendein mapping problem, nichts wichtiges
  _kickSlider.setValue(map(kick.getPower(), 70, 255, 0, 100)+1);
}

//Calibrate BallTouch
void Display::ballTouchBall(void *ptr)
{
  _caliBall = true;
  _ballTouchBall.Set_background_color_bco(34785);
  ballTouch.calibrateBall();
  if(_caliNoBall)
    _ballTouchThreshold.Set_background_color_bco(1462);
}

void Display::ballTouchNoBall(void *ptr)
{
  _caliNoBall = true;
  _ballTouchNoBall.Set_background_color_bco(34785);
  ballTouch.calibrateNoBall();
  if(_caliBall)
    _ballTouchThreshold.Set_background_color_bco(1462);
}

void Display::ballTouchThreshold(void *ptr)
{
  if(_caliBall && _caliNoBall)
  {
    _ballTouchStatus.setText("Calibrated");
    ballTouch.calculateTreshold();
    _caliBall = false;
    _caliNoBall = false;
  }else if(_caliBall)
    _ballTouchStatus.setText("Calibrate NoBall");
  else if(_caliNoBall)
    _ballTouchStatus.setText("Calibrate Ball");
}

//Hardware BallTouch


//Hardware Enable/Disable
void Display::switchEnKick(void *ptr)
{
  kick.setEn(!kick.getEn());
}

void Display::switchEnChassis(void *ptr)
{
  m.setMotEn(!m.getMotEn());
}

void Display::switchEnCmps(void *ptr)
{
  cmps.setEn(!cmps.getEn());
}

void Display::switchEnCam(void *ptr)
{
  camera.setEn(!camera.getEn());
}

void Display::switchEnUs(void *ptr)
{
  us.setEn(!us.getEn());
}

void Display::switchEnBallt(void *ptr)
{
  ballTouch.setEn(!ballTouch.getEn());
}

void Display::switchEnBt(void *ptr)
{
  bt.setEn(!bt.getEn());
}

void Display::switchEnPui(void *ptr)
{
  pui.setEn(!pui.getEn());
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
  kick.setPower(map(number, 0, 100, 70, 255));
}

//Hardware Chassis
//attach to enMotos






void Display::init()
{
  nexInit(); // Register the pop event callback function of the components

  //Overview
  _goRAM.attachPop(goRAM, &_goRAM);
  _goState.attachPop(goState, &_goState);

  //Hardware
  _goHardBallt.attachPop(goHardBallt, &_goHardBallt);
  _goHardKick.attachPop(goHardKick, &_goHardKick);
  _goHardChassis.attachPop(goHardChassis, &_goHardChassis);

  //Config
  _goEnDisable.attachPop(goEnDisable, &_goEnDisable);

  //Config calibrate
  _goCaliKick.attachPop(goCaliKick, &_goCaliKick);

  //Cali BallTouch
  _ballTouchBall.attachPop(ballTouchBall, &_ballTouchBall);
  _ballTouchNoBall.attachPop(ballTouchNoBall, &_ballTouchNoBall);
  _ballTouchThreshold.attachPop(ballTouchThreshold, &_ballTouchThreshold);

  //Hardware BallTouch


  //Hardware Enable/Disable
  _enKick.attachPop(switchEnKick, &_enKick);
  _enChassis.attachPop(switchEnChassis, &_enChassis);
  _enCmps.attachPop(switchEnCmps, &_enCmps);
  _enCam.attachPop(switchEnCam, &_enCam);
  _enUs.attachPop(switchEnUs, &_enUs);
  _enBallt.attachPop(switchEnBallt, &_enBallt);
  _enBt.attachPop(switchEnBt, &_enBt);
  _enPui.attachPop(switchEnPui, &_enPui);

  //Hardware Kicker
  _kickBall.attachPop(kickBall, &_kickBall);
  _enKick2.attachPop(switchEnKick, &_enKick2);

  //Cali Kicker
  _kickBall2.attachPop(kickBall, &_kickBall2);
  _kickSlider.attachPop(kickSlider, &_kickSlider);

  //Hardware Chassis
  _enChassis2.attachPop(switchEnChassis, &_enChassis2);
  LogDisplay("Initilized");
}

void Display::update()
{
  nexLoop(_nex_listen_list);
}
