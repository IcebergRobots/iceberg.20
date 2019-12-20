#include "Display.h"

     // You might need to change NexConfig.h file in your ITEADLIB_Arduino_Nextion folder
  // Set the baudrate which is for debug and communicate with Nextion screen
  NexText Display::_tLedState  = NexText(2, 4, "t0");
  NexButton Display::_bLedOn = NexButton(2, 5, "b1");
  NexButton Display::_bLedOff = NexButton(2, 6, "b2");
  NexSlider Display::_hLedSlider = NexSlider(2, 3, "h0");

NexTouch *Display::_nex_listen_list[NUM_OBJECTS] = {
  &_bLedOn,
  &_bLedOff,
  &_hLedSlider,
  NULL
};

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

void Display::init() {
      nexInit();  // Register the pop event callback function of the components

  _bLedOn.attachPop(bLedOnPopCallback, &_bLedOn);
  _bLedOff.attachPop(bLedOffPopCallback, &_bLedOff);
  _hLedSlider.attachPop(hLedSliderPopCallback);
  pinMode(_led1, OUTPUT);

}

void Display::update() {
      nexLoop(_nex_listen_list);
}
