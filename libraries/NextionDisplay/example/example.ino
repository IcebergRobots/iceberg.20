/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */

#include "Nextion.h"
// LED pins
const int led1 = 13;

// Declare your Nextion objects - Example (page id = 0, component id = 1, component name = "b0") 
NexText tState = NexText(2, 4, "t0"); 
NexButton bOn = NexButton(2, 5, "b1");
NexButton bOff = NexButton(2, 6, "b2");
NexSlider h0 = NexSlider(2, 3, "h0");

// Register a button object to the touch event list.  
NexTouch *nex_listen_list[] = {
  &bOn,
  &bOff,
  &h0,
  NULL
};
 
/*
 * Button bOn component pop callback function. 
 * When the ON button is released, the LED turns on and the state text changes. 
 */
void bOnPopCallback(void *ptr) {
  tState.setText("State: on");
  digitalWrite(led1, HIGH);
}

/*
 * Button bOff component pop callback function. 
 * When the OFF button is released, the LED turns off and the state text changes. 
 */
void bOffPopCallback(void *ptr) {
  tState.setText("State: off");
  digitalWrite(led1, LOW);
}

/*
 * Slider h0 component pop callback function. 
 * When the slider is released, the LED brightness changes and the slider text changes. 
 */
void h0PopCallback(void *ptr) {
  uint32_t number = 0;
  char temp[10] = {0};
  // change text with the current slider value
  h0.getValue(&number);
  utoa(number, temp, 10);
  // change LED brightness
  analogWrite(led1, number); 
}


void setup(void) {    
  Serial.begin(9600);
    
  // You might need to change NexConfig.h file in your ITEADLIB_Arduino_Nextion folder
  // Set the baudrate which is for debug and communicate with Nextion screen
  nexInit();

  // Register the pop event callback function of the components
  bOn.attachPop(bOnPopCallback, &bOn);
  bOff.attachPop(bOffPopCallback, &bOff);
  h0.attachPop(h0PopCallback);    
  // Set LEDs as outputs
  pinMode(led1, OUTPUT);
}

void loop(void) {   
  /*
   * When a pop or push event occured every time,
   * the corresponding component[right page id and component id] in touch event list will be asked.
   */
  nexLoop(nex_listen_list);
}
