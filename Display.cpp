#include "Display.h"

/*
 * Button bOn component pop callback function. 
 * When the ON button is released, the LED turns on and the state text changes. 
 */
void Display::bOnPopCallback(void *ptr) {
    tState.setText("State: on");
    digitalWrite(led1, HIGH);
}

/*
 * Button bOff component pop callback function. 
 * When the OFF button is released, the LED turns off and the state text changes. 
 */
void Display::bOffPopCallback(void *ptr) {
  tState.setText("State: off");
  digitalWrite(led1, LOW);
}

/*
 * Slider h0 component pop callback function. 
 * When the slider is released, the LED brightness changes and the slider text changes. 
 */
void Display::h0PopCallback(void *ptr) {
  uint32_t number = 0;
  char temp[10] = {0};
  // change text with the current slider value
  h0.getValue(&number);
  utoa(number, temp, 10);
  // change LED brightness
  analogWrite(led1, number); 
}

void Display::init() {
     // You might need to change NexConfig.h file in your ITEADLIB_Arduino_Nextion folder
  // Set the baudrate which is for debug and communicate with Nextion screen
  nexInit();  // Register the pop event callback function of the components
  tState  = NexText(2, 4, "t0");
  bOn = NexButton(2, 5, "b1");
  bOff = NexButton(2, 6, "b2");
  h0 = NexSlider(2, 3, "h0");

  *nex_listen_list[3] = {&bOn, &bOff, &h0};
  
  bOn.attachPop(bOnPopCallback, &bOn);
  bOff.attachPop(bOffPopCallback, &bOff);
  h0.attachPop(h0PopCallback);
  pinMode(led1, OUTPUT);
}
