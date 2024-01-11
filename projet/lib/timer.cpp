/*
 * Nom du fichier: timer.cpp
 * Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
 * Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
 * Equipe #57-#58
 * Date: 26 octobre 2022
 * Description: Definition des methodes de la classe Timer declaree dans le fichier timer.cpp
 */
#include "timer.h"
void Timer::initDefault(uint16_t duration)
{
    cli();
    TCNT1 = 0;
    OCR1A = duration;
    TCCR1A |= (1 << COM1A0);                            // compare output mode A
    TCCR1B |= (1 << CS10) | (1 << CS12) | (1 << WGM12); // prescale 1024, CTC mode
    TCCR1C = 0;
    TIMSK1 |= (1 << OCIE1A); // interrupt quand counter match ocr1a
    sei();
}
void Timer::setClkScale(ClkScale clkScale)
{
    cli();
    switch (clkScale)
    {
    case ClkScale::clk1:
        TCCR1B |= (1 << CS10);
        break;
    case ClkScale::clk8:
        TCCR1B |= (1 << CS11);
        break;
    case ClkScale::clk64:
        TCCR1B |= ((1 << CS11) | (1 << CS10));
        break;
    case ClkScale::clk256:
        TCCR1B |= (1 << CS12);
        break;
    case ClkScale::clk1024:
        TCCR1B |= ((1 << CS12) | (1 << CS10));
        break;
    }
    sei();
}
void Timer::setTimer(uint16_t duration)
{
    OCR1A = duration;
    TIMSK1 |= (1 << OCIE1A);
}
void Timer::stopTimer()
{
    OCR1A = 0;
    TIMSK1 = 0;
}
bool Timer::timerDelay(uint16_t delay)
{
    setTimer(delay);
    if (maxValueCounter == 1)
    {
        setTimer(0);
        return true;
    }
    return false;
}