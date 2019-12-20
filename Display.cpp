#include "Display.h"

extern BallTouch ballTouch;
extern Chassis m;

/*******************************************************************
 * Example
 * ******************************************************************/

     // You might need to change NexConfig.h file in your ITEADLIB_Arduino_Nextion folder
  // Set the baudrate which is for debug and communicate with Nextion screen
  NexText Display::_tLedState  = NexText(2, 4, "t0");
  NexButton Display::_bLedOn = NexButton(2, 5, "b1");
  NexButton Display::_bLedOff = NexButton(2, 6, "b2");
  NexSlider Display::_hLedSlider = NexSlider(2, 3, "h0");


  
  //Calibrate BallTouch
  NexButton Display::_ballTouchBall = NexButton(7,3,"b1");
  NexButton Display::_ballTouchNoBall = NexButton(7,4,"b2");
  NexButton Display::_ballTouchThreshold = NexButton(7,5,"b3");
  NexText Display::_ballTouchStatus = NexText(7,6,"t0");

  //Sensor BallTouch
NexText Display::_caliStatus = NexText(8,3,"t0");
NexText Display::_ballStatus = NexText(8,4,"t1");
NexButton Display::_updateStatus = NexButton(8,5,"b1");

//Sensor Enable Disable
NexDSButton Display::_enKick = NexDSButton(9,3,"kicken");
NexDSButton Display::_enMotors = NexDSButton(9,6,"motorsen");
NexButton Display::_updateEnable = NexButton(9,7,"b1");

NexTouch *Display::_nex_listen_list[NUM_OBJECTS] = {
  //Example
  &_bLedOn,
  &_bLedOff,
  &_hLedSlider,

  //Cali BallTouch
  &_ballTouchBall,
  &_ballTouchNoBall,
  &_ballTouchThreshold,

  //Sensor BallTouch
  &_updateStatus,

  //Sensor enable Disable
  &_enKick,
  &_enMotors,
  &_updateEnable,

  NULL
};

/*******************************************************************
 * Example
 * ******************************************************************/
/*
 * Button _bLedOn component pop callback function. 
 * When the ON button is released, the LED turns on and the state text changes. 
 */
void Display::bLedOnPopCallback(void *ptr) {
    _tLedState.setText("State: on");
    digitalWrite(_led1, HIGH);
}

/*
 * Button _bLedOff component pop callback function. 
 * When the OFF button is released, the LED turns off and the state text changes. 
 */
void Display::bLedOffPopCallback(void *ptr) {
  _tLedState.setText("State: off");
  digitalWrite(_led1, LOW);
}

/*
 * Slider _hLedSlider component pop callback function. 
 * When the slider is released, the LED brightness changes and the slider text changes. 
 */
void Display::hLedSliderPopCallback(void *ptr) {
  uint32_t number = 0;
  char temp[10] = {0};
  // change text with the current slider value
  _hLedSlider.getValue(&number);
  utoa(number, temp, 10);
  // change LED brightness
  analogWrite(_led1, number); 
}


//Calibrate BallTouch
void Display::ballTouchBall(void *ptr){
  ballTouch.calibrateBall();
}

void Display::ballTouchNoBall(void *ptr) {
  ballTouch.calibrateNoBall();
  
}

void Display::ballTouchThreshold(void *ptr) {
  ballTouch.calculateTreshold();
  calibrated = true;
  _ballTouchStatus.setText("Calibrated Succesfully");
  if (!caliNoBall)
  {
    _ballTouchStatus.setText("Calibrated NoBall");
    calibrated = false;
  }
  if (!caliBall)
  {
    _ballTouchStatus.setText("Calibrated Ball");
    calibrated = false;
  }
  
}

//Sensors BallTouch
void Display::updateBallStatus(void *ptr) {
  if (calibrated)
  {
    _caliStatus.setText("Sees Ball?");
    if (ballTouch.hasBall())
  {
    _ballStatus.setText("Yes");
  }else
  {
    _ballStatus.setText("No");
  }
  }

}


//Sensor Enable/Disable
void Display::switchEnKick(void *ptr) {
  enKick = !enKick;
}

void Display::enMotors(void *ptr) {
  m.setMotEn(!m.getMotEn());
}

void Display::updateEnabled(void *ptr) {
  if (enKick)
  {
    _enKick.setValue(1);
  }else
  {
    _enKick.setValue(0);
  }
  
  if (m.getMotEn())
  {
    _enMotors.setValue(1);
  }else
  {
    _enMotors.setValue(0);
  }
}

void Display::init() {
      nexInit();  // Register the pop event callback function of the components

  //Example
  _bLedOn.attachPop(bLedOnPopCallback, &_bLedOn);
  _bLedOff.attachPop(bLedOffPopCallback, &_bLedOff);
  _hLedSlider.attachPop(hLedSliderPopCallback);
  pinMode(_led1, OUTPUT);


  //Cali BallTouch
  _ballTouchBall.attachPop(ballTouchBall, &_ballTouchBall);
  _ballTouchNoBall.attachPop(ballTouchNoBall, &_ballTouchNoBall);
  _ballTouchThreshold.attachPop(ballTouchThreshold, &_ballTouchThreshold);

  //Sensor BallTouch
  _updateStatus.attachPop(updateBallStatus, &_updateStatus);

  //Sensor Enable/Disable
  _enKick.attachPop(switchEnKick, &_enKick);
  _enMotors.attachPop(enMotors, &_enMotors);
  _updateEnable.attachPop(updateEnabled, &_updateEnable);

}

void Display::update() {
      nexLoop(_nex_listen_list);    
}
