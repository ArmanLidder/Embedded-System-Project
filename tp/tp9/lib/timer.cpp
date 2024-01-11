/*
 * Nom du fichier: timer.cpp
 * Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
 * Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
 * Equipe #57-#58
 * Date: 26 octobre 2022
 * Description: Definition des methodes de la classe Timer declaree dans le fichier timer.cpp
 */

#include "timer.h"
const uint8_t MAX_COUNT = 255;


void Timer::initDefault(uint8_t duration)
{
    cli();
    TCNT0 = 0;
    TCCR0A |= ((1 << WGM01));
    TCCR0B |= ((1 << CS02) | (1 << CS00));
    TIMSK0 = (1 << OCIE0B);
    OCR0A = duration;
    sei();
}

void Timer::setClkScale(ClkScale clkScale)
{
    cli();
    switch (clkScale) {
        case ClkScale::clk1:
            TCCR0B |= (1 << CS00);
            break;
        case ClkScale::clk8:
            TCCR0B |= (1 << CS01);
            break;
        case ClkScale::clk64:
            TCCR0B |= ((1 << CS01) | (1 << CS00));
            break;
        case ClkScale::clk256:
            TCCR0B |= (1 << CS02);
            break;
        case ClkScale::clk1024:
            TCCR0B |= ((1 << CS02) | (1 << CS00));
            break;
    }
    sei();
}

void Timer::setTimer(uint8_t duration) 
{
    OCR0A = duration;
}