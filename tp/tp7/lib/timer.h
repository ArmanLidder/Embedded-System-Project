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
        void initDefault(uint8_t duration);
        void setTimer(uint8_t duration);
        void setClkScale(ClkScale clkScale);
};
