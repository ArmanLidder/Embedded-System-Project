#pragma once
#include "includes.h"
// #define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "motor.h"
#include "LED.h"
#include "timer.h"
#include "debug.h"
#include "FollowLineTrajetA.h"
// assignation des ports
// PORT A2 IR 01
// PORT A3 IR 02
// PORT A4 IR 03
// PORT A5 IR 04
// PORT A1 IR 05
volatile extern bool timerDone;
void updateLine(uint8_t &line);
void followLineS(Motor &motor, uint8_t &line);
void parking(Motor& motor, uint8_t &line);
void commeBackOnLine(Motor &motor, uint8_t &line);
void followLineStraight(Motor &motor, uint8_t &line, Timer &counter);
void turnLeftZigZag(Motor &motor, Timer &counter, uint8_t &line);
void turnRightZigzag(Motor &motor, uint8_t &line);
void followLineZigzag(Motor &motor, Timer &counter, uint8_t &line);
void searchU1(Motor &motor, uint8_t &line);
void targetSVisitor(Motor &motor, Timer &counter, uint8_t &line);
void followRouteS();