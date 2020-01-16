#include "Utility.h"


void kick() {
    if (millis() - kickTimer > 333) {
    kickTimer = millis();
    while (millis() - kickTimer <50)
    {
        analogWrite(KICKER, map(analogRead(A0),0,1023,190,255));    // schuss bei 12, Poti bei A0
    }
           kickTimer = millis(); 
    analogWrite(12,0);
  }
}

void startSound() {
  //Fiepen, welches Programstart signalisiert
  
  for (int i = 10; i < 2000; i += 10) {
    // if(isTypeA)
    // tone(BUZZER, i);
    // else
    tone(13, 2010-i);
    
    delay(1);
  }
  noTone(13);
}