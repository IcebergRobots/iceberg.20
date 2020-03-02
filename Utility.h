#pragma once

#include "Config.h"

void startSound();

void reset();

#define HEARTBEAT_LOOPTIME 500
void heartbeat();

extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;
uint16_t getFreeSRAM();


static bool initChooseRobot = true;
static bool robot;
bool chooseRobot(); 