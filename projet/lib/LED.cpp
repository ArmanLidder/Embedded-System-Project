/*
* Nom du fichier: LED.cpp
* Arman Lidder : 2174916  - Hamza Boukaftane : 2183376
* Loic Nguemegne-Temena : 2180845 - Jonathan Arrobas-Gilbert: 2120128
* Equipe #57-#58
* Date: 26 octobre 2022
* Description: Definition des methodes de la classe LED declaree dans le fichier LED.h
*/

#include "LED.h"

const uint8_t AMBER_DELAY = 10;

Led::Led(volatile uint8_t *port,volatile uint8_t *ddrx, int pinOne, int pinTwo)
{
    ddrx_ = ddrx;
    port_ = port;
    pinOne_ = pinOne;
    pinTwo_ = pinTwo;

    *ddrx_ |= (_BV(pinOne_));
    *ddrx_ |= (_BV(pinTwo_));
}

void Led::setLedOff()
{
    *port_ &= ~ (_BV(pinOne_));
    *port_ &= ~ (_BV(pinTwo_));
}

void Led::setLedGreen()
{
    *port_ &= ~(_BV(pinOne_));
    *port_ |= _BV(pinTwo_);
}

void Led::setLedRed()
{
    *port_ &= ~(_BV(pinTwo_));
    *port_ |= _BV(pinOne_);
}

void Led::setLedAmbreOnce()
{
    setLedGreen();
    _delay_ms(AMBER_DELAY);
    setLedRed();
    _delay_ms(AMBER_DELAY);
}

void Led::setLedAmbreLoop(uint16_t loopTime)
{
    uint16_t nIterations = loopTime/(AMBER_DELAY*2); // on a x2 car on appelle ce delay deux fois
    for (uint16_t i=0; i<nIterations;i++)
        setLedAmbreOnce();
    setLedOff();
}
