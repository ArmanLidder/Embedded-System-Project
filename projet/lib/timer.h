/*
* Nom du fichier: timer.h
* Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
* Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
* Equipe #57-#58
* Date: 26 octobre 2022
* Description: Declaration de la classe Timer et de ses methodes
*/
#pragma once
#include <avr/interrupt.h>
const uint16_t MAX_COUNT = 65535;
const uint16_t oneSecond = 7812;
const uint16_t twoSecond = 15625;
const uint16_t twoAndHalfSecond = 19531;
const uint16_t threeSecond = 23437;
const uint16_t fourSecond = 31250;
const uint16_t fiveSecond = 39062;
const uint16_t sixSecond = 46875;
const uint16_t sevenSecond = 54687;
const uint16_t eightSecond = 62500;
enum class ClkScale 
{
    clk1,
    clk8,
    clk64,
    clk256,
    clk1024
};
class Timer
{
    public:
        void initDefault(uint16_t duration=0);
        void setTimer(uint16_t duration);
        void setClkScale(ClkScale clkScale);
        bool timerDelay(uint16_t delay);
        void stopTimer();
    private:
    uint8_t maxValueCounter = 0;
};