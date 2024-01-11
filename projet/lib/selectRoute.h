#pragma once
#include "includes.h"
// #define F_CPU 8000000
#include "LED.h"
#include "ButtonInterruption.h"
#include <util/delay.h>
const uint8_t D2_INACTIVE = 0x04;
const uint8_t QUARTER_SECOND = 125;
static volatile uint8_t currentState = 0;
static volatile bool isStart = false;

int selectRoute();