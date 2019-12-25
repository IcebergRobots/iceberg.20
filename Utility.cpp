#include "Utility.h"

void kick()
{
  if (millis() - kickTimer > 333 && enKick && caliKick)
  {
    kickTimer = millis();
    while (millis() - kickTimer < 50)
    {
      analogWrite(KICKER, kickPower); // schuss bei 12, Poti bei A0
    }
    kickTimer = millis();
    analogWrite(KICKER, 0);
  }
}

void startSound()
{
  //Fiepen, welches Programstart signalisiert

  for (int i = 10; i < 2000; i += 10)
  {
    // if(isTypeA)
    // tone(BUZZER, i);
    // else
    tone(BUZZER, 2010 - i);

    delay(1);
  }
  noTone(BUZZER);
}