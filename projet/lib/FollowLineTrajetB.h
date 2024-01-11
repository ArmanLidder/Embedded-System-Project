#pragma once
#include "includes.h"
// #define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "motor.h"
#include "LED.h"
#include "distanceSensor.h"
#include "memoire_24.h"
// #include "debug.h"
#include "timer.h"
#include "LED.h"
#include "FollowLineTrajetA.h"
// assignation des ports
// PORT A2 IR 01
// PORT A3 IR 02
// PORT A4 IR 03
// PORT A5 IR 04
// PORT A1 IR 05


uint8_t readLineBSensor();
void clockwiseRotation(Motor &motor);
void rollback(Motor &motor);
void antiCockwiseRotation(Motor &motor);
void adjustMotor(Motor &motor);



void adjustLeft(Motor &motor);

void adjustRight(Motor &motor);

void followLineB(Motor &motor, uint8_t &captorOnB, uint8_t &status, bool &isRunning);

void followLineBT(Motor &motor, uint8_t &captorOnB, uint8_t &status, bool &isRunning);

void followRouteB();



