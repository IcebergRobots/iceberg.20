#include<EEPROM.h>

//MUX-Bits - D0 is MSB & D3 is LSB
#define D0 9
#define D1 8
#define D2 10
#define D3 11

//ANALOG OUTPUTS MULTIPLEXER
#define S1 A3
#define S2 A2
#define S3 A1

#define SWITCH A6
#define BUZZER A0

#define INTERRUPT_PIN   7                 //INTERRUPT PIN                    
#define MUX_EN          12

#define CALIBRATION_TIME 5000
#define MULTIPLICATOR 50


byte  binPins[] = {D0, D1, D2, D3};       //four pins to declare transistor 
byte  ledPins[] = {2, 3, 4, 5, 6};
int  traNum[]  = {0, 1, 2, 3, 8, 9, 10, 11, 16, 17, 18, 19, 24, 25, 26, 27};
int  angles[]  = {0, 90, 180, 270};

unsigned long timer; 
String bin;
byte sendValue = -1;

int raw[32];

int value[16];
int hit[16];
int defect[16];
int threshold[16];

int maxValue[16];
int minValue[16];

bool line;

int angle = 0;



namespace Line {

  void init(){
    for (int i = 2; i <= 13; i++) {     //digital pins set to input
      pinMode(i, INPUT);
    }

    for (int i = 0; i < 5; i++) {
      pinMode(ledPins[i], OUTPUT);
    }

    pinMode(BUZZER, OUTPUT);
    pinMode(SWITCH, INPUT_PULLUP);

    pinMode(INTERRUPT_PIN, OUTPUT);


    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);

    pinMode(S1, INPUT);
    pinMode(S2, INPUT);
    pinMode(S3, INPUT);

    pinMode(MUX_EN, OUTPUT);
    digitalWrite(MUX_EN, LOW);
  }

  void measure(){
    bool state;

    for (int counter = 0; counter < 16; counter++) {
      hit[counter] = false;

      bin = String(counter, BIN);
      int binlength = bin.length();

      for (int i = 0; i < 4 - binlength; i++) {
        bin = "0" + bin;
      }

      for (int i = 0; i < 4; i++) {
        if (bin[i] == '0') state = LOW;
        if (bin[i] == '1') state = HIGH;
        digitalWrite(binPins[i], state);
      }

      delayMicroseconds(1);

      raw[counter] = analogRead(S1);
      raw[counter + 16] = analogRead(S2);
    }
    for(int i = 0; i < 16; i++){
      value[i] = raw[traNum[i]];
    }
  }  
  
  void calibrate(){
    digitalWrite(ledPins[0], HIGH);
    for(int i = 0; i < 16; i++){
      minValue[i] = 2000;
      maxValue[i] = 0;
    }
    unsigned long calibration_Timer = millis() + 10000;
    Serial.println("Callibration Timer" + (String) calibration_Timer);
    while (millis() < calibration_Timer){
      measure();
    
      for (int i = 0; i < 16; i++) {
        Serial.print((String) i + " - " + value[i]);
        Serial.println(""); 
        if (value[i] < minValue[i])
          minValue[i] = value[i];
        if (value[i] > maxValue[i])
          maxValue[i] = value[i];
      }
    }
    for(int i = 0; i < 16; i++){    
      Serial.println((String) i + " - " + maxValue[i] + "|" + minValue[i]);
      threshold[i] = (2*minValue[i] + maxValue[i]) / 3;
      if (maxValue[i] - minValue[i] < 10)
        threshold[i] = 0;
    }
    digitalWrite(ledPins[0], LOW);
  }

  void send(){
    angle = constrain(angle, 0, 360);
    if(sendValue == -1){
      sendValue = angle;
    }
    byte output = (byte) map(angle, 0, 360, 0, 255);
    Serial.write(output);
  }

  void interrupt() {
    digitalWrite(INTERRUPT_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(INTERRUPT_PIN, LOW);
    delayMicroseconds(10);
  } 

  void update(){
    angle = 0;
    line = false;
    measure();
    for(int i = 0; i < 16; i++){
      if(value[i] > threshold[i]){
        line = true;
        hit[i] = true;
        if(i < 4){
          angle = angles[0];
        }else if(i < 8){
          angle = angles[1];
        }else if(i < 12){
          angle = angles[2];
        }else if(i < 16){
          angle = angles[3];
        }else{
          Serial.println("Something went wrong.");
        }
      }
    }
    if(line){
      digitalWrite(ledPins[5], HIGH);
      send();
      interrupt();
    }else{
      sendValue = -1;
      digitalWrite(ledPins[5], LOW);
    }
  }

  

  void debug(){
    for(int i = 0; i < 16; i++){
      Serial.print((String) i + threshold[i] + ",");
    }
    Serial.println("angle: " + (String) angle);
  }
}



/*********************************************************************************************************
 SETUP 
 *********************************************************************************************************/
void setup() {
  Serial.begin(115200);

  Line::init();
  Line::calibrate();
}

/*********************************************************************************************************
 LOOP 
 *********************************************************************************************************/
void loop() {
  Line::measure();
  
  Line::update();

  //Line::send();
  //Line::interrupt();
 

  //Line::interrupt();
  delay(500);

}






