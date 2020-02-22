#pragma once

#include "Config.h"

void startSound();

void reset();

void heartbeat();

extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;
uint16_t getFreeSRAM();