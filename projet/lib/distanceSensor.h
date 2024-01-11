#pragma once
#include "can.h"
#include "Sound.h" 
#include "motor.h"
static const uint8_t FAR_REGION_MAX = 50;
static const uint8_t FAR_REGION_MIN = 32;
static const uint8_t CLOSE_REGION_MAX = 120;
static const uint8_t CLOSE_REGION_MIN = 60;

enum poleDetection
{
    POLE_DETECTED_CLOSE,
    POLE_DETECTED_FAR,
    POLE_NOT_DETECTED
};
bool isFar();
bool isClose();
int checkPoleDistance(poleDetection &pole);