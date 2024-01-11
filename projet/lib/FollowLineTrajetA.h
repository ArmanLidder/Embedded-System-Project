#pragma once
#include "includes.h"
// #define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "motor.h"
#include "distanceSensor.h"
#include "memoire_24.h"

enum CaptorOn
{
    U1 = 4,
    U5 = 2,
    U2 = 8,
    U3 = 16,
    U4 = 32,
    U1_U2 = 12,
    U4_U5 = 34,
    U1_U5 = 6,
    U1_U4 = 36,
    U2_U5 = 10,
    U2_U4 = 40,
    U1_U2_U3 = 28,
    U2_U3_U4 = 56,
    U1_U2_U3_U4 = 60,
    U2_U3_U4_U5 = 58,
    U3_U4_U5 = 50,
    U1_U2_U3_U4_U5 = 62,
    NOTHING = 0,
};

uint8_t readLineASensor();
void followLineA(Motor &motor, uint8_t &captorLed, uint8_t &status, bool &isRunning);
void followLineATemporarily(Motor &motor);
void followRouteA();