#include "Utility.h"

void startSound()
{
  //Fiepen, welches Programstart signalisiert

  for (int i = 10; i < 2000; i += 10)
  {
    if (isRobotA)
      tone(BUZZER, i);
    else
      tone(BUZZER, 2010 - i);

    delay(1);
  }
  noTone(BUZZER);
}

uint16_t getFreeSRAM()
{
  uint8_t newVariable;
  // heap is empty, use bss as start memory address
  if ((uint16_t)__brkval == 0)
    return (((uint16_t)&newVariable) - ((uint16_t)&__bss_end));
  // use heap end as the start of the memory address
  else
    return (((uint16_t)&newVariable) - ((uint16_t)__brkval));
}

void reset()
{
  asm("jmp 0"); // starte den Arduino neu
}

void heartbeat()
{
  byte i = map(millis() % HEARTBEAT_LOOPTIME * 2, 0, HEARTBEAT_LOOPTIME, 0, 255);
  analogWrite(HEARTBEAT_LED, i > 255 ? i : 255 - i);
}

bool chooseRobot()
{
  if (initChooseRobot)
  {
    pinMode(HARDWARE_DIFFERENCE, INPUT_PULLUP);
    if (digitalRead(HARDWARE_DIFFERENCE) == HIGH)
    {
      LogUtility("Robot A started");
      isRobotA = true;
    }
    else
    {
      LogUtility("Robot B started");
      isRobotA = false; //RObot B
    }

    initChooseRobot = false;
  }
  return isRobotA;
}